

#ifndef OZ_EVENTOBJ_H
#define OZ_EVENTOBJ_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "engine.h"
#include "movablenode.h"
#include "movable.h"
#include "animation.h"
#include "map.h"
#include "rand.h"

class EventObj
    : public Movable
{
    public:
        EventObj( Engine &e, MovableNode *node, MovableMapNode &mapnode  )
            :  Movable( e, node, mapnode ), engine( &e )
        { }

        EventObj( const EventObj &n  )
            :  Movable( n ), engine( n.engine )
        { }

        ~EventObj()
        {}

        void ai( F32, Map &, vector<Movable *> & );
        void hit( Movable *, Map &, vector< Movable *> & );

    private:
        Engine      *engine;
};

#endif

