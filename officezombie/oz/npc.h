

#ifndef OZ_NPC_H
#define OZ_NPC_H

#include <cmath>

#include <SFML/Graphics.hpp>
using namespace sf;

#include "engine.h"
#include "movablenode.h"
#include "movable.h"
#include "animation.h"
#include "map.h"
#include "rand.h"
#include "state_event.h"

class NPC
    : public Movable
{
    public:
        NPC( Engine &e, MovableNode *node, MovableMapNode &mapnode  )
            :  Movable( e, node, mapnode ), engine( &e ), random(), zombieSound()
        { }

        NPC( const NPC &n  )
            :  Movable( n ), engine( n.engine ), random()
        { 
            //zombieSound.ResetBuffer();
        }
        
        ~NPC()
        {}

        void ai( F32, Map &, vector<Movable *> & );
        //MovType type() { return NPC_TYPE; }
        void hit( Movable *, Map &, vector< Movable *> & );

        void humanai( F32, Map &, vector< Movable *> & );
        void randomai( F32, Map &, vector< Movable *> & );
        void zombieai( F32, Map &, vector< Movable *> & );

    private:
        Engine      *engine;
        Random      random;

        Sound       zombieSound;
};

#endif

