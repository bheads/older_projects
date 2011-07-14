

#ifndef OZ_Puzzle_H
#define OZ_Puzzle_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "engine.h"
#include "movablenode.h"
#include "movable.h"
#include "animation.h"
#include "map.h"
#include "rand.h"

class Puzzle
    : public Movable
{
    public:
        Puzzle( Engine &e, MovableNode *node, MovableMapNode &mapnode  )
            :  Movable( e, node, mapnode ), engine( &e )
        { }

        Puzzle( const Puzzle &n  )
            :  Movable( n ), engine( n.engine )
        { }
        
        ~Puzzle()
        {}

        void ai( F32, Map &, vector<Movable *> & );
        void hit( Movable *, Map &, vector< Movable *> & );

    private:
        Engine      *engine;
};

#endif

