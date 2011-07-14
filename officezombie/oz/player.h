

#ifndef OZ_PLAYER_H
#define OZ_PLAYER_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "movablenode.h"
#include "movable.h"
#include "fmacs.h"
#include "engine.h"
#include "animation.h"
#include "map.h"

#include "state_puzzle.h"
#include "state_event.h"

class Player
    : public Movable
{
    public:
        Player( Engine &e, MovableNode *node, MovableMapNode &mapnode )
            : Movable( e, node, mapnode ), engine( e ), rdir( 0 ), restore( false ), zombieSound()
        {}

        Player( const Player &p )
            : Movable( p ), engine( p.engine ), rdir( p.rdir ), restore( p.restore )
        {
            //zombieSound.ResetBuffer();
        }

        ~Player()
        {}

        void ai( F32, Map &, vector<Movable *> & );
        void hit( Movable *, Map &, vector<Movable *> & );
        Movable *infront( Map &, vector<Movable*> & );
        bool trypull( Direction dir, Map &map, vector<Movable*> &movables );

        void changemap( PuzzleNode & );
        void runevent( EventNode & );


        GETSET( U32, exp, engine.data.playernode.exp )
        GETSET( U32, max_exp, engine.data.playernode.max_exp )
        GETSET( U32, exp_mult, engine.data.playernode.exp_mult )
        GETSET( U32, level, engine.data.playernode.level )
        GETSET( U32, map_id, engine.data.playernode.map_id )
        GETSET( U32, green, engine.data.playernode.green_id )
        GETSET( U32, red, engine.data.playernode.red_id )
        F32 scale();

    private:
        Engine      &engine;
        U32         rdir;
        bool        restore;

        Sound       zombieSound;
};


#endif

