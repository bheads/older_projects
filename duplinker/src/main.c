/*
   duplinker - Scans a directory looking for files that contain the same data
            as other files in the same path tree.  Duplicate files are 
            replaced with a hard link.  This should be used on files that do
            not get changed.  The is being purposed for the use with radmind
            servers.  This maybe is a problem when you merge a load set.
*/

#define __USE_LARGEFILE64
#define _LARGEFILE_SOURCE
#define _LARGEFILE64_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h> 
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <openssl/sha.h>

#include "uthash.h"


#define VERSION "0.01a"
#define NAME "duplinker"
#define HASH_LEN (( SHA256_DIGEST_LENGTH * 2 ) + 1 )

void print_help();
void print_version();
void process( char * );
int scan_path( char path[ PATH_MAX ], uint32_t tablevel );
void ptabs( uint32_t tabs );
char *trim( char *str );
int hashFile( const char *filename, char hash[ HASH_LEN ] );

void add( char *hash, char *fname, ino_t inode );
struct hash_node *find( char *hash );
void delete_all();


int dryrun = 0, verbose = 0, version = 0, help = 0, quite = 0, 
    scanlinks = 0, cleartable = 0;;
#define VERBOSE( B ) if( verbose && !quite ) { B; }
#define NORMAL( B ) if( !quite || verbose ) { B; }


struct hash_node {
    char id[ HASH_LEN ]; /* key */
    char fname[ PATH_MAX ]; /* file name of first file hash to match id */
    ino_t   inode;  /* inode of file, used for dups that may already be hardlinks */
    UT_hash_handle hh;
};

struct hash_node *files = NULL;

int main( int argc, char **argv )
{
    int opt = -1, opt_idx = 0; 

    static struct option duplinker_options[] = 
    {
        { "dry-run", no_argument, 0, 'd' },
        { "verbose", no_argument, 0, 'v' },
        { "version", no_argument, 0, 'V' },
        { "help", no_argument, 0, 'h' },
        { "quite", no_argument, 0, 'q' },
        { "scan-links", no_argument, 0, 's' },
        { "clear", no_argument, 0, 'c' },
        {0,0,0,0}
    };

    while((opt = getopt_long( argc, argv, "dvVhqsc", duplinker_options, 
                    &opt_idx )) > 0 ) {
        switch( opt ) {
            case 'd':
                dryrun = 1;
                break;
            case 'v':
                verbose = 1;
                quite = 0;
                break;
            case 'V':
                version = 1;
                break;
            case 'h':
                help = 1;
                break;
            case 'q':
                quite = 1;
                verbose = 0;
                break;
            case 'c':
                cleartable = 1;
                break;
            case 's':
                scanlinks = 1;
                break;
            default:
                NORMAL( printf( "Try \'%s --help\' for more information.\n", NAME ));
                exit(1);
                break;
        }
    }

    if( help ) print_help();
    if( version ) print_version();

    if( optind == argc ) {
        NORMAL( fprintf( stderr, "Requires a path to scan for duplicate files\n" ));
        print_help();
    }

    while( optind < argc ) {
        VERBOSE( printf( "Scanning %s:\n", argv[optind] ));
        /* do the scan here */
        process( argv[optind++] );
        if( cleartable ) delete_all();
    }

    delete_all();
    return( 0 );
}

void print_help()
{
    printf( "%s {OPTIONS} PATH1 PATH2\n\n"
            "Scans the given paths for duplicate files, if there are any it\n"
            "converts the duplicate into a hardlinks.  Used to save storage\n"
            "space on radmind servers that may contain many transcripts that\n"
            "have duplicated data\n\n"
            " \t-d --dry-run\tOnly find duplicates,\n"
            "\t\t\tand do not make the hard links\n"
            " \t-h --help\tPrint this help\n"
            " \t-v --verbose\tDetailed output\n"
            " \t-V --version\tProgram version\n"
            " \t-q --quite\tSuppress output\n"
            " \t-s --scan-links\tAllows scanning of symlinks\n"
            " \t-c --clears\tClears the file table between PATHS\n"
            "\n", NAME);
            

    exit( 0 );
}


void print_version()
{
    printf( "%s version %s\n", NAME, VERSION );
    exit( 0 );
}

void process( char *path )
{
    if( path == NULL ) {
        NORMAL( fprintf( stderr, "Process was passed a NULL string\n" ));
        return;
    }

    if( scan_path( path, 0 )) {
        VERBOSE( fprintf( stderr, "Failed to scan %s: %s\n", path, 
                    strerror(errno )));
    }
}

int scan_path( char path[ PATH_MAX ], uint32_t tablevel )
{
    struct stat64 statdir, statfile;
    struct dirent *entry;
    DIR *dir;
    char fname[ PATH_MAX ], hash[ HASH_LEN ];
    uint32_t len;
    int ret;
    struct hash_node *node;

    // add / at end of path
    len = strlen( path );
    if( len == 0 || len > PATH_MAX ) {
        fprintf( stderr, "Got a bad path: |%s|\n", path );
        return 1;
    }
    if( path[len-1] != '/' ) {
        strncpy( fname, path, sizeof( fname ));
        if( snprintf( path, PATH_MAX, "%s/", fname ) >= PATH_MAX ) {
            fprintf( stderr, "Path is to long: %s\n", path );
            return 1;
        }
    }

    // try to stat
    if( scanlinks ) {
        // stat64 follows the symlink, thus our link check is always false
        if( stat64( path, &statdir ) != 0 ) {
            NORMAL( fprintf( stderr, "Path %s does not exist: %s\n", path, 
                        strerror( errno )));
            return errno;
        }
    } else {
        if( lstat64( path, &statdir ) != 0 ) {
            NORMAL( fprintf( stderr, "Path %s does not exist: %s\n", path, 
                        strerror( errno )));
            return errno;
        }
    }

    // make sure this is a directory
    if( !S_ISDIR( statdir.st_mode ) || S_ISLNK( statdir.st_mode )) {
        NORMAL( fprintf( stderr, "%s is not a directory\n", path ));
        if( S_ISLNK( statdir.st_mode ))
            NORMAL( fprintf( stderr, 
                        "Scanning links is disabled by defaults\n" ));
        return errno;
    }

    // open the directory
    if(( dir = opendir( path )) == NULL ) {
        NORMAL( fprintf( stderr, "Failed to open %s: %s\n", path, 
                    strerror( errno )));
        return errno;
    }

    while(( entry = readdir( dir ))) {

        // skip . and ..
        if( strcmp( entry->d_name, "." ) == 0 ||
                strcmp( entry->d_name, ".." ) == 0 ) {
            continue;
        }
        // build full file name
        // path is checked if it has a / at the end
        if( snprintf( fname, sizeof( fname ), "%s%s", path, entry->d_name ) >=
                sizeof( fname )) {
            fprintf( stderr, "File name is to long: %s\n", fname );
            closedir( dir );
            return 1;
        }

        // try to stat
        if( scanlinks ) {
            // stat64 follows the symlink, thus our link check is always false
            if( stat64( fname, &statfile ) != 0 ) {
                NORMAL( fprintf( stderr, "Failed to stat %s: %s\n", fname, 
                            strerror( errno )));
                continue;
            }
        } else {
            if( lstat64( fname, &statfile ) != 0 ) {
                NORMAL( fprintf( stderr, "Failed to stat %s: %s\n", fname, 
                            strerror( errno )));
                continue;
            }
        }

        if( S_ISREG( statfile.st_mode ) && !S_ISLNK( statfile.st_mode )) {
            VERBOSE( ptabs( tablevel ); printf( "%-30s %-10lld", entry->d_name, 
                        statfile.st_size );
                    fflush( stdout ); );
            // get the files hash code
            if(( ret = hashFile( fname, hash )) != 0 ) {
                continue;
            }
            //VERBOSE( printf( " %s ", hash ));
            if(( node = find( hash )) == NULL ) {
                VERBOSE( printf( "Unmatched\n" ));
                add( hash, fname, statfile.st_ino );
            } else {
                if( statfile.st_ino == node->inode ) {
                    VERBOSE( printf( "Matched - Already Hardlink\n" ));
                } else {
                    if( !verbose ) NORMAL( printf( "%s is ", fname ));
                    NORMAL( printf( "Matched - Making Hardlink of %s: ", node->fname );
                            fflush( stdout));
                    if( !dryrun ) {
                        if( unlink( fname ) != 0 ) {
                            NORMAL( printf( "failed %s\n", strerror( errno )));
                            continue;
                        }
                        if( link( node->fname, fname ) != 0 ) {
                            NORMAL( printf( "failed %s\n", strerror( errno )));
                            continue;
                        }
                        NORMAL( printf( "done\n"));
                    } else {
                        NORMAL( printf( "skipped\n"));
                    }
                }
            }
        } else if ( S_ISDIR( statfile.st_mode ) && !S_ISLNK( statfile.st_mode )) {
            VERBOSE( ptabs( tablevel ); printf( "%-30s\n", fname ));
            if(( ret = scan_path( fname, tablevel + 1 )) != 0 ) {
                continue;
            }
        }
    }

    closedir( dir );
    return( 0 );
}

void ptabs( uint32_t tabs ) 
{
    while( tabs-- > 0 ) printf( "    " );
}

char *trim( char *str )
{
    char *f = str, *t, *e;
    if( str == NULL ) return NULL;

    while( isspace( *f++ ));
    e = t = --f;
    while( *t != '\0' ) { 
        if( !isspace( *t )) e = t;
        ++t;
    }

    *++e = '\0';
    if( f > str ) memmove( str, f, e - f + 1 ); 
    
    return str;
}



int hashFile( const char *filename, char hash[ HASH_LEN ] )
{
    uint8_t hashret[ HASH_LEN ], buf[10240];
    SHA256_CTX sha256;
    int rr, fp;

    // open file to read from
    if(( fp = open( filename, O_RDONLY )) < 0 ) {
        NORMAL( fprintf( stderr, "Failed to open %s for hashing: %s\n",
                    filename, strerror( errno )));
        return errno;
    }

    SHA256_Init( &sha256 );
    while(( rr = read( fp, buf, sizeof( buf ))) > 0 ) {
        SHA256_Update( &sha256, buf, rr );
    }
    if( rr != 0 ) {
        NORMAL( fprintf( stderr, "Failed to read from %s: %s\n", filename,
                    strerror( errno )));
        close( fp );
        return errno;
    }
    SHA256_Final( hashret, &sha256 );

    close( fp );

    memset( hash, 0, HASH_LEN );
    for( rr = 0; rr < SHA256_DIGEST_LENGTH; ++rr ) {
        sprintf( hash + ( rr * 2 ), "%02x", hashret[rr] );
    }
    return 0;
}

void add( char *hash, char *fname, ino_t inode )
{
    struct hash_node *node;

    if(( node = (struct hash_node*)malloc( sizeof(struct hash_node))) 
            == NULL ) {
        fprintf( stderr, "Failed to malloc hash node: %s\n", 
                strerror( errno ));
        exit( errno );
    }
    strncpy( node->id, hash, sizeof( node->id ));
    strncpy( node->fname, fname, sizeof( node->fname ));
    node->inode = inode;

    HASH_ADD_STR( files, id, node );
}

struct hash_node *find( char *hash )
{
    struct hash_node *node;
    HASH_FIND_STR( files, hash, node );
    return node;
}


void delete_all()
{
    struct hash_node *node, *tmp;

    HASH_ITER( hh, files, node, tmp ) {
        HASH_DEL( files, node );
        free( node );
    }
}
