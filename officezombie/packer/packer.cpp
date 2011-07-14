
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include "stdtype.h"
#include "error.h"
#include "hash.h"
#include "filefunc.h"
#include "config.h"
#include "map.h"

I32 resources( string, string, string );
ERRCODE module( string, string );
I32 help();

struct node
{
    U32 hash;
    U32 offset;
    U32 size;
    U32 strlen;

    void print( string & str ) {
        cout << "\n\tHASH: " << hash << endl;
        cout << "\tOFFSET: " << offset << endl;
        cout << "\tSIZE: " << size << endl;
        cout << "\tSTRLEN: " << strlen << endl;
        cout << "\tSTR: \"" << str << "\"" << endl;
    }

    void write( FILE * fp ) 
    {
        //debug( cout << "\tstart@: " << ftell( fp ) << endl );
        enforce( fwrite( &hash, 1, 4, fp ) == 4,
                "Failed to write: " << strerror( errno ));

        //debug( cout << "\thash@ " << ftell( fp ) << endl );
        enforce( fwrite( &offset, 1, 4, fp ) == 4,
                "Failed to write: " << strerror( errno ));

        //debug( cout << "\toffset@ " << ftell( fp ) << endl );
        enforce( fwrite( &size, 1, 4, fp ) == 4,
                "Failed to write: " << strerror( errno ));

        //debug( cout << "\tsize@ " << ftell( fp ) << endl );
        enforce( fwrite( &strlen, 1, 4, fp ) == 4,
                "Failed to write: " << strerror( errno ));

        //debug( cout << "\tstrlen@ " << ftell( fp ) << endl );
    }
};

I32 main( I32 argc, char ** argv )
{
    string path, package;
    if( argc != 3 ) {
        return( help( ));
    }

    path = argv[1];
    if( path[ path.size() - 1 ] != '/' ) path += '/';
    package = argv[2];

    debug(
        vector<string> strlist;
        string test = "0ne;102;105;;;;;";
        stringSep( test, strlist, ';' );
        assert( strlist.size() == 3, "" );
        cout << strlist[0] << " " << strlist[1] << " " << strlist[2]<< endl;
        );

    resources( path + "resources/", package + ".pkr", package + "_resources.txt" );
    module( path + "module/", package + ".mod" );


    return( 0 );
}


I32 resources( string path, string package, string rlist )
{
    string base;
    vector<string> files;
    vector<node*> header;
    map<U32, string> test;
    node *tmp;
    U32 foffset = sizeof( U32 ), hcnt = 0;
    I32 rr = 0;
    U8 rbuf[10240];
    FILE *fp = NULL, *rfp = NULL;

    cout << "Packing directory " << path << " into " << package << endl;

    // find all of our files
    debug( cout << "Scanning: " << path << endl );
    GetFileList( files, path, base );   
    sort( files.begin(), files.end());

    // Build package header
    debug( cout << "\nBuilding header: " << endl );
    // prebuild
    for( size_t i = 0; i < files.size(); ++i ) {
        tmp = new node();
        tmp->hash = ap( files[i] );
        tmp->offset = 0;
        tmp->size = FileSize( path + files[i] );
        tmp->strlen = files[i].size();
        foffset += sizeof( node ) + tmp->strlen;
        header.push_back( tmp );
        enforce( test.find( tmp->hash ) == test.end(), "Hash collision: "
                << test[ tmp->hash ] << " <-> " << files[i] );
        test[ tmp->hash ] = files[i];
        debug( cout << "\t" << tmp->hash << " -> " << files[i] << endl );
    }
    // now setup the offsets
    for( size_t i = 0; i < header.size(); ++i ) {
        header[i]->offset = foffset;
        debug( cout << "\t" << files[i] << " offset at " << foffset << endl ); 
        foffset += header[i]->size;
    }

    // write pack header out
    debug( cout << "\nWriting header: " << endl );
    // open file
    enforce(( fp = fopen( package.c_str(), "wb" )) != NULL,
                    "Failed to open " << package << " for output: " << 
                    strerror( errno ));

    // write out number of nodes in header
    hcnt = header.size();
    enforce( fwrite( &hcnt, sizeof( U32 ), 1, fp ) == 1,  
            "write failure ( " << strerror( errno ) << " )" << endl );
    debug( cout << "\theader has " << hcnt << " nodes" <<  endl ); 

    for( size_t i = 0; i < header.size(); ++i ) {
        U32 start = ftell( fp ), end;
        //enforce( fwrite( header[i], sizeof( node ), 1, fp ) == 1,
        //        "write failure ( " << strerror( errno ) << " )" << endl );
        header[i]->write( fp );
        end = ftell( fp );
        enforce(( end - start ) == sizeof( node ), "Out of sync!" );
        enforce( fwrite( files[i].c_str(), files[i].size(), 1, fp ) == 1,
                "write failure ( " << strerror( errno ) << " )" << endl );
        debug( cout << "\t\t@ " << ftell( fp ) << endl );
    }
    debug( cout << "\theader ends at offset " << ftell( fp ) << endl ); 

    // write file data
    debug( cout << "\nWriting filedata: " << endl );
    for( size_t i = 0; i < header.size(); ++i ) {
        base = path + files[i];
        debug( cout << "\twriting file " << files[i] << " at offset " <<
                ftell( fp  ) << endl );
         enforce( ftell( fp ) == header[i]->offset, "Pack file not synced!!" );
                    
        enforce(( rfp = fopen( base.c_str(), "rb" )) != NULL ,
                "Failed to open " << base << " for reading: " << 
                strerror( errno ));
        while(( rr = fread( rbuf, 1, 10240, rfp )) > 0 ) {
            enforce( fwrite( rbuf, 1, rr, fp ) == rr,
                "write failure ( " << strerror( errno ) << " )" << endl );
        }

        fclose( rfp );
    }

    fclose( fp );
    cout << "Done!" << endl;

    cout << "Writting Resource List to: " << rlist << endl;
    fp = NULL;
    enforce(( fp = fopen( rlist.c_str(), "wb" )) != NULL,
                    "Failed to open " << rlist << " for output" );
    for( map<U32, string>::iterator i = test.begin(); i != test.end(); ++i ) {
        stringstream ss;
        ss << i->first << " --> " << i->second << endl;
        string line = ss.str();
        enforce( fwrite( line.c_str(), line.size(), 1, fp ) == 1,  
                "write failure ( " << strerror( errno ) << " )" << endl );
    }

    fclose( fp );
    cout << "Done!" << endl;

    for( IDX i = 0; i < header.size(); ++i ) {
        delete header[i];
        header[i] = NULL;
    }
    header.clear();

	return( PK_OK );
}


ERRCODE module( string path, string package )
{
    string base;
    vector<string> files;
    Config  config;
    Map     map;
    FILE *fp = NULL;

    debug( "Building module pack " );

    // find all of our files
    debug( cout << "Scanning: " << path << endl );
    GetFileList( files, path, base );   
    sort( files.begin(), files.end());
    debug( cout << "Done" << endl );

    debug( cout << "Writing mod file: " << package << endl );
    enforce(( fp = fopen( package.c_str(), "wb" )) != NULL,
                    "Failed to open " << package << " for output" );

    for( size_t i = 0; i < files.size(); ++i ) {
        //if( contains( files[i], '*' )) {
        if( files[i].find( ".csv" ) != string::npos ) {
            // process as a map file
            map.loadmap( path + files[i] );
            map.writemap( fp );
        } else {
            // process as a config file
            config.load( path + files[i] );
            config.writebin( fp );
        }
    }

    fclose( fp ); 
    debug( cout << "Done" << endl );
    return( PK_OK );
}


I32 help()
{
    cout << "OZ File Packer...  We pack them real good!" << endl;
    cout << "\tpkr requires a path to pack up, and a pack name." << endl;
    cout << "Usage: pkr [PATH] [PACK NAME]" << endl;
    cout << "\t./pkr ../data/ oz\n" << endl;
    return( PK_OK );
}

