


#ifndef OZ_RENDERMAP_H
#define OZ_RENDERMAP_H

#include <SFML/Graphics.hpp>
using namespace std;

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "error.h"
#include "stdtype.h"
#include "engine.h"
#include "map.h"
#include "movablenode.h"
#include "npc.h"
#include "box.h"
#include "puzzle.h"
#include "event.h"
#include "player.h"

class RenderMap
{
    public:
        RenderMap( Engine &e )
            : engine( e ), map( NULL ), npclist(), boxlist(), puzzlelist(),
            player( e, &(e.data.movables[ e.data.playernode.mapnode.movable_id ]),
                    e.data.playernode.mapnode ), movables()
        {}
        ~RenderMap()
        {
            clear();
        }

        void clear();
        void build( Map &map );
        void update( F32 );
        void draw( I32 ox, I32 oy, I32, I32, F32, F32 );

        Engine          &engine;
        Map             *map;
        vector<NPC*>    npclist;
        vector<Box*>    boxlist;
        vector<Puzzle*> puzzlelist;
        vector<EventObj*>  eventlist;
        Player          player;

        vector<Movable*>    movables;
};

#endif

