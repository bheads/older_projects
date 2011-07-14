

#ifndef OZ_MOVABLE_H
#define OZ_MOVABLE_H

#include <cmath>

#include <SFML/Graphics.hpp>
using namespace sf;

#include <vector>
using namespace std;

#include <cmath>

#include "movablenode.h"
#include "fmacs.h"
#include "engine.h"
#include "animation.h"
#include "map.h"

extern Direction rdirection[];

class Movable
{
    public:
        Movable( Engine &e, MovableNode *node, MovableMapNode &mapnode )
            : engine( e ), _base( node ), _mapbase( mapnode ), anim(),
            movemod( engine.config.get( "Engine:MoveMod", PY_MOVEMOD, true )),
            _rx( mapnode.x ), _ry( mapnode.y ), _offset( 0.0 ), _moving( false )
        {
            enforce( _base->id == _mapbase.movable_id,
                    "Movable Map Node id is different" );
        }

        Movable( const Movable &m )
            : engine( m.engine ), _base( m._base ), _mapbase( m._mapbase ), anim(),
            movemod( engine.config.get( "Engine:MoveMod", PY_MOVEMOD, true )),
            _rx( m._mapbase.x ), _ry( m._mapbase.y ), _offset( 0.0 ), _moving( false )
        {
            enforce( _base->id == _mapbase.movable_id,
                    "Movable Map Node id is different" );
        }

        virtual ~Movable()
        {}

        void setanim();
        void update( F32 );
        virtual void ai( F32, Map &, vector<Movable *> & ) = 0;
        void draw( F32, F32, F32, F32, F32, F32 );
        void trymove( Map &map, vector<Movable *> &, bool test = true );

        void collision( Map &map, vector<Movable *> & );
        //virtual MovType type() { return UNKNOWN_TYPE; }
        virtual void hit( Movable *hit, Map &map, vector<Movable *> & ) = 0;

        I32 dist( Movable & );
        U32 face( Movable & );
        U32 back( Movable & );

        I32 xoffset() { return rx() - x(); }
        I32 yoffset() { return ry() - y(); }

        GETSET( U32, id, _base->id )
        GETSET( MovableNode *, base, _base )
        GETSET( MovableMapNode &, mapbase, _mapbase )
        REFGETSET( I32, x, _mapbase.x )
        REFGETSET( I32, y, _mapbase.y )
        REFGETSET( U32, type, _mapbase.type )
        REFGETSET( I32, rx, _rx )
        REFGETSET( I32, ry, _ry )
        REFGETSET( F32, offset, _offset )
        REFGETSET( U32, direction, _mapbase.direction )
        REFGETSET( U32, alive, _mapbase.alive )
        REFGETSET( bool, moving, _moving )
        REFGETSET( U32, mutable_id, _mapbase.mutable_id)


        MovableMapNode  &_mapbase;

    private:
        Engine      &engine;
        MovableNode     *_base;
        Animation   anim;
        F32         movemod;

        I32         _rx, _ry;
        F32         _offset;
        bool        _moving;
};


#endif

