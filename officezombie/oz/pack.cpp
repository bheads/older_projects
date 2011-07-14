
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "pack.h"


PackManager::PackManager()
    : _open( false ), fp( NULL ), packs()
{}

PackManager::~PackManager()
{
    if( _open ) {
        fclose( fp );
        _open = false;
    }
}

void PackManager::load( string filename )
{
    node    tmp;
    char    tmpstr[ 1024 ];
    U32     count, rr;

    if( _open ) {
        fclose( fp );
        _open = false;
    }

    enforce(( fp = fopen( filename.c_str(), "rb" )) != NULL, 
            "Failed to open " << filename << ": " << strerror( errno ));
    _open = true;

    // read node count
    enforce(( rr = fread( &count, 1, sizeof( U32 ), fp )) == sizeof( U32 ),
            "Failed to read header node count from pack." );

    // read the nodes
    for( size_t i = 0; i < count; ++i ) {
        // read node base
        enforce(( rr = fread( &tmp, 1, sizeof( node ), fp )) == 
                sizeof( node ), "Failed to read header node from pack." );
        // read node string
        enforce(( rr = fread( &tmpstr, 1, tmp.strlen, fp )) == tmp.strlen,
                "Failed to read header node string from pack." );
        tmpstr[rr] = '\0';
        packs[ tmp.hash ] = pack( tmp, tmpstr );
        /*
        debug(
                cout << "\n" << tmp.hash << " --> " << tmpstr << endl;
                cout << tmp.offset << " -> " << tmp.offset + tmp.size << endl;
             );
         */
    }
}


U8 *PackManager::getNEWdata( U32 hash, U32 &size )
{
    U8 *data;
    pack p;

    enforce( packs.find( hash ) != packs.end(), hash << " not in map!" );

    p = packs[ hash ];
    data = new U8[ p.size ];
    fseek( fp, p.offset, SEEK_SET );
    enforce( fread( data, 1, p.size, fp ) == p.size, 
            "Failed to read data from pack file" );
    size = p.size;

    return( data );
}

