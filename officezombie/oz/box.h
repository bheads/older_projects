

#ifndef OZ_BOX_H
#define OZ_BOX_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "engine.h"
#include "movablenode.h"
#include "movable.h"
#include "animation.h"
#include "map.h"

class Box
    : public Movable
{
    public:
        Box( Engine &e, MovableNode *node, MovableMapNode &mapnode  )
            :  Movable( e, node, mapnode ), engine( &e ) 
        { }

        Box( const Box &b  )
            :  Movable( b ), engine( b.engine ) 
        { }
        
        ~Box()
        {}

        void ai( F32, Map &, vector<Movable *> & );
        void hit( Movable *, Map &, vector<Movable *> & );

    private:
        Engine      *engine;
};

#endif

