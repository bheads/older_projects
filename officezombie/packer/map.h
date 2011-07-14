
#ifndef PK_MAP_H
#define PK_MAP_H


#include <string>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "error.h"
#include "stdtype.h"
#include "strfunc.h"
#include "filefunc.h"

#define BLOCKED 1<<0
#define N_BLOCKED 1<<1
#define E_BLOCKED 1<<2
#define S_BLOCKED 1<<3
#define W_BLOCKED 1<<4

#ifndef MIN
#define MIN( a, b ) ( a <= b ? a : b )
#endif

U32 convert( string & );
U32 convert( const char * );

struct MapTile
{
    U32     tile_id;
    U32     block;
    U32     static_id[4];

    MapTile( string &str )
        : tile_id( convert( str  )), block( 0 ), static_id()
    {
        vector<string> list;
        stringSep( str, list, ';' );

        for( IDX i = 0; i < 4; ++i ) {
            if( list.size() > i + 1 ) {
                static_id[i] = convert( list[i+1] );
            } else {
                static_id[i] = 0;
            }
        }

        if( contains( str, 'b' ) || contains( str, 'B' )) block |= BLOCKED;
        if( contains( str, 'n' ) || contains( str, 'N' )) block |= N_BLOCKED;
        if( contains( str, 'e' ) || contains( str, 'E' )) block |= E_BLOCKED;
        if( contains( str, 's' ) || contains( str, 'S' )) block |= S_BLOCKED;
        if( contains( str, 'w' ) || contains( str, 'W' )) block |= W_BLOCKED;

    }

    void print()
    {
        cout << "[ " << tile_id << " ";
        if( block & BLOCKED ) cout << "B";
        if( block & N_BLOCKED ) cout << "N";
        if( block & E_BLOCKED ) cout << "E";
        if( block & S_BLOCKED ) cout << "S";
        if( block & W_BLOCKED ) cout << "W";
        cout << ";" << static_id;
        cout <<  " ]" << endl;
    }

};

struct NPCNode
{
    U32     npc_id;
    I32     x, y;
    U32     direction;
    U32     alive;
    U32     type;
    U32     mut_id;

    NPCNode()
        : npc_id( 0 ), x( 0 ), y( 0 ), direction( 0 ), alive( 1 ), type( 0 ), mut_id( 0 )
    {}

    NPCNode( const NPCNode &n )
        : npc_id( n.npc_id ), x( n.x ), y( n.y ), direction( n.direction ),
        alive( n.alive ), type( n.type ), mut_id( n.mut_id )
    {}
};

class Map
{
    public:
        Map()
            : id( 0 ), name(), width( 0 ), height( 0 ), tilemap(), npclist(), 
            hloaded( false )
        {}
        ~Map()
        {}

        void clear();
        void loadmap( string );
        void writemap( FILE * );

    private:
        U32     id;
        string  name;
        U32     width, height;
        vector<MapTile> tilemap;
        vector<NPCNode> npclist;
        bool    hloaded;

        template <class T> void writeBlock( FILE *, T * );
        void writeString( FILE *, string & );
};

#endif

