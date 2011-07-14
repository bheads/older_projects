

#include "movable.h"

Direction rdirection[] = { South, West, North, East };

void Movable::setanim()
{
    if( !alive()) return;
    if( moving()) {
        switch( direction()) {
            case North:
                anim.set( engine.data.animation[ _base->n_hash ], engine.images );
                break;
            case East:
                anim.set( engine.data.animation[ _base->e_hash ], engine.images );
                break;
            case South:
                anim.set( engine.data.animation[ _base->s_hash ], engine.images );
                break;
            case West:
                anim.set( engine.data.animation[ _base->w_hash ], engine.images );
                break;
        }
    } else {
        switch( direction()) {
            case North:
                anim.set( engine.data.animation[ _base->sn_hash ], engine.images );
                break;
            case East:
                anim.set( engine.data.animation[ _base->se_hash ], engine.images );
                break;
            case South:
                anim.set( engine.data.animation[ _base->ss_hash ], engine.images );
                break;
            case West:
                anim.set( engine.data.animation[ _base->sw_hash ], engine.images );
                break;
        }
    }
}


void Movable::update( F32 delta )
{
    if( !alive()) return;
    setanim();

    if( moving()) {
        if( !anim.isrunning()) anim.runloop();
        offset() += ( delta * movemod );
        if( offset() >= 1.0f ) {
            moving( 0 );
            offset( 0.0f );
            rx( x());
            ry( y());
            anim.stop();
            setanim();
        }
    }

    anim.update( delta );
}

void Movable::draw( F32 x1, F32 y1, F32 x, F32 y, F32 hw, F32 hh )
{
   F32 wx = 0.0f, wy = 0.0f;
   F32 ox = 0.0f, oy = 0.0f;
   if( !alive()) return;

   switch( direction()) {
       case North:
           oy = -offset();
           break;
       case East:
           ox = offset();
           break;
       case South:
           oy = offset();
           break;
       case West:
           ox = -offset();
           break;
   }

   wx = x1 + (( x + ox ) * hw ) + (( y + oy ) * hw );
   wy = y1 + (( y + oy ) * hh ) - (( x + ox ) * hh );
   anim.position( wx - (((((F32)anim.getw() / 2.0f ) -  hw ))/2.0f),
           (wy - (F32)anim.geth()) + hh + hh );
   anim.draw( engine.gfx );
}


void Movable::collision( Map &map, vector<Movable *> &movables )
{
    if( !alive()) return;
    if( x() < 0  || y() < 0 || x() >= map.Width() || y() >= map.Height() ||
            map( x(), y() ).block & BLOCKED ||
            map( rx(), ry() ).block & block_dir[ direction() ] ||
            map( x(), y() ).block & block_rdir[ direction() ] ) {
        x( rx());
        y( ry());
        moving( false );
        return;
    }

    for( IDX i = 0; i < movables.size(); ++i ) {
        if( this != movables[i] && movables[i]->alive()) {
            if( x() == movables[i]->x() &&
                    y() == movables[i]->y() &&
                    movables[i]->alive()) {
                x( rx());
                y( ry());
                moving( false );
                hit( movables[i], map, movables );
            }
        }
    }
}

void Movable::trymove( Map &map, vector<Movable *> &movables, bool test )
{
   if( !alive() || moving()) {
       return;
   }
   rx( x());
   ry( y());
   switch( direction()) {
       case North:
           y()--;
           break;
       case East:
           x()++;
           break;
       case South:
           y()++;
           break;
       case West:
           x()--;
           break;
       default:
           enforce( false, "Bad Direction!" );
   }

   moving( 1 );
   if( test ) {
       collision( map, movables );
   }
}



U32 Movable::face( Movable &m )
{
    I32 dx = m.rx() - rx();
    I32 dy = m.ry() - ry();

    if( dx == 0 ) {
        if( dy < 0 ) {
            direction( North );
        } else {
            direction( South );
        }
    } else if( dy == 0 ) {
        if( dx > 0 ) {
            direction( East );
        } else {
            direction( West );
        }
    } else {
        if( abs( dx ) < abs( dy )) {
            if( dx > 0 ) {
                direction( East );
            } else {
                direction( West );
            }
        } else {
            if( dy < 0 ) {
                direction( North );
            } else {
                direction( South );
            }
        }
    }

    return direction();
}

U32 Movable::back( Movable &m )
{
    I32 dx = m.rx() - rx();
    I32 dy = m.ry() - ry();

    if( dx == 0 ) {
        if( dy < 0 ) {
            direction( South );
        } else {
            direction( North );
        }
    } else if( dy == 0 ) {
        if( dx > 0 ) {
            direction( West );
        } else {
            direction( East );
        }
    } else {
        if( abs( dx ) < abs( dy )) {
            if( dx > 0 ) {
                direction( West );
            } else {
                direction( East );
            }
        } else {
            if( dy < 0 ) {
                direction( South );
            } else {
                direction( North );
            }
        }
    }

    return direction();
}


I32 Movable::dist( Movable &m )
{
    register I32 dx = abs( m.rx() - rx() );
    register I32 dy = abs( m.ry() - ry() );
    register I32 d = sqrt( dx * dx + dy * dy );

    return d;
}

