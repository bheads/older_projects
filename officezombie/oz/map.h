

#ifndef OZ_MAP_H
#define OZ_MAP_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "mod_resource.h"
#include "movablenode.h"


#define BLOCKED 1<<0
#define N_BLOCKED 1<<1
#define E_BLOCKED 1<<2
#define S_BLOCKED 1<<3
#define W_BLOCKED 1<<4

extern U32 block_dir[4];
extern U32 block_rdir[4];

struct MapNode
{
    U32 id, width, height, strlen;

};

struct TileNode
{
    U32 tile_id, block, static_id[4];
};

class Map
    : public ModResource
{
    public:
        Map()
            : ModResource( 0 ), width( 0 ), height( 0 ), name(), loaded( false ),
            tilemap( NULL ), npcs()
        {}
        ~Map()
        {
            clear();
        }

        void clear();
        void read( FILE *, string & );
        void write( FILE *, string & );

        TileNode & operator()( U32, U32 );

        U32 Width() { return width; }
        U32 Height() { return height; }
        bool Loaded() { return loaded; }
        U32 humanCount();

    private:
        U32 width, height;
        bool loaded;
        TileNode **tilemap;

    public:
        vector<MovableMapNode>  npcs;
        string name;

};

#endif

