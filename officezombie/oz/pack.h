

#ifndef OZ_PACK_H
#define OZ_PACK_H

#include <vector>
#include <map>
#include <string>
using namespace std;

#include <stdlib.h>
#include <stdio.h>

#include "stdtype.h"
#include "error.h"

struct node
{
    U32 hash;
    U32 offset;
    U32 size;
    U32 strlen;
};

struct pack
{
    pack()
        : hash( 0 ), offset( 0 ), size( 0 ), filename()
    {}

    pack( const pack &p )
        : hash( p.hash ), offset( p.offset ), size( p.size ), filename( p.filename )
    {}

    pack( node n, char *str )
        : hash( n.hash ), offset( n.offset ), size( n.size ), filename( str )
    {}

    U32 hash;
    U32 offset;
    U32 size;
    string filename;
};

class PackManager
{
    public:
        PackManager();
        ~PackManager(); 

        void load( string filename );
        U8 *getNEWdata( U32 hash, U32 &size );

    private:
        bool    _open;
        FILE    *fp;

    public:
        map<U32, pack> packs;
};

#endif





