/***
 * filefunc.cpp
 *  collection of useful file functions.
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

// use stat to test if file exists
#include <sys/stat.h> 
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#include "filefunc.h"

// Test if a file/dir exists
bool FileExists( const string &filename ) 
{ 
    struct stat filestat;
    return(( stat( filename.c_str(), &filestat ) == 0 ));
}

bool GetFileList( vector<string> &files, string &path, string &base )
{
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    string file, full, tmp;

    if( path[ path.size() - 1 ] != '/' ) path += "/";
    if( base.size() > 1 && base[ base.size() - 1 ] != '/' ) base += "/";

    //open path
    enforce(( dp = opendir( path.c_str())) != NULL, "Unable to open " << path
            << "( " << strerror( errno ) << " )" << endl );

    while(( dirp = readdir( dp )) != NULL ) {
        file = dirp->d_name;
        full = path;
        full += file;
        
        if( strcmp( file.c_str(), "." ) == 0 || 
                strcmp( file.c_str(), ".." ) == 0 ) {
            continue;
        }

        if( stat( full.c_str(), &filestat ) == 0 ) {
            if( S_ISREG( filestat.st_mode )) { 
                debug( cout << "\tF: " << base + file << endl );
                files.push_back( base + file );
            } else if( S_ISDIR( filestat.st_mode )) {
                debug( cout << "Scanning: " << full << endl );
                tmp = base + file;
                GetFileList( files, full, tmp );
            } else {
                debug( cout << "\tIgnoring " << file << endl );
            }
        } else {
            cout << "\t! Cannot access " << full << " ( " << strerror( errno ) 
                << " )" << endl;
        }
    }

    // close path
    enforce( closedir( dp ) == 0, "Failed to close " << path << " ( " << 
            strerror( errno ) << " )" << endl );

    return( PK_OK );
}


U32 FileSize( const string file )
{
    U32 size = 0;
    FILE *fp = fopen( file.c_str(), "r" );
    fseek( fp, 0, SEEK_END );
    size = ftell( fp );
    fclose( fp );
    return( size );
}

// read a line of text from a FILE stream
ssize_t readline( char **lineptr, size_t *n, FILE *stream )
{
    ssize_t size = -1;
    char *buf = NULL, *p;
    U32 c;

    // make sure we have valid ptrs
    if( lineptr == NULL ) return -1;
    if( n == NULL ) return -1;
    if( stream == NULL ) return -1;

    size = *n;
    buf = *lineptr;

    // test if we are at the end of the file
    if(( c = fgetc( stream )) == EOF ) {
        return -1;
    }

    // test if we have a buffer
    if( buf == NULL ) {
        if(( buf = (char *)malloc( 1024 )) == NULL ) {
            return -1;
        }
        size = 1024;
    }
    p = buf;

    // scan till EOF or Newline
    do {
        // make sure buf is large enough, -1 for the \0
        if(( p - buf ) > ( size - 1 )) {
            size += 1024;
            if(( buf = (char *)realloc( buf, size )) == NULL ) {
                fseek( stream, -1 * size, SEEK_CUR );
                return -1;
            }
        }
        *p++ = c;
        if( c == '\n' ) break;
    } while(( c = fgetc( stream )) != EOF );

    *p++ = '\0';
    *lineptr = buf;
    *n = size;

    return p - buf - 1;
}


