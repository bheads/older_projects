

#include "npc.h"

extern U32 zombiesfx[7];
extern U32 blood[];

void NPC::ai( F32 delta, Map &map, vector<Movable *> &movables )
{
    if( NPC_MALE_TYPE <= type() && type() <= NPC_FEMALE_TYPE ) {
        humanai( delta, map, movables );
    } else if( ZOMBIE_MALE_TYPE <= type() && type() <= ZOMBIE_FEMALE_TYPE ) {
        zombieai( delta, map, movables );
    }

}

void NPC::humanai( F32 delta, Map &map, vector<Movable *> &movables )
{
    for( IDX  i = 0; i < movables.size(); ++i ) {
        if( movables[i]->type() == PLAYER_TYPE || 
                movables[i]->type() == ZOMBIE_MALE_TYPE ||
                movables[i]->type() == ZOMBIE_FEMALE_TYPE ) {
            if( dist( *(movables[i])) <= 3 && !moving()) {
                back( *movables[i] );
                trymove( map, movables );
                if( !moving()) {
                    direction() = ( direction() + 1 ) % 4;
                    trymove( map, movables );
                    if( !moving()) {
                        direction() = ( direction() + 2 ) % 4;
                        trymove( map, movables );
                    }
                }
            }
            if( moving()) return;
        }

    }

    if( !moving()) {
        randomai( delta, map, movables );
    }
}
void NPC::randomai( F32 delta, Map &map, vector<Movable *> &movables ) 
{
    I32 d;
    if( !moving()) {
         d = random.nextInt( 0, 150 );
         switch( d ) {
            case 0:
            case 1:
            case 2:
            case 3:
                direction( d );
                break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                trymove( map, movables );
                break;
            default:
                break;
        }
    }
}

void NPC::zombieai( F32 delta, Map &map, vector<Movable *> &movables )
{
    for( IDX  i = 0; i < movables.size(); ++i ) {
        if( movables[i]->type() == NPC_MALE_TYPE || 
                movables[i]->type() == NPC_FEMALE_TYPE ) {
            if( dist( *(movables[i])) <= 3 && !moving()) {
                face( *movables[i] );
                trymove( map, movables );
                if( !moving()) {
                    direction() = ( direction() + 1 ) % 4;
                    trymove( map, movables );
                    if( !moving()) {
                        direction() = ( direction() + 2 ) % 4;
                        trymove( map, movables );
                    }
                }
            }
            if( moving()) return;
        }

    }


    if( !moving()) {
        face( *movables[0] );
        trymove( map, movables );
        if( !moving()) {
            direction() = ( direction() + 1 ) % 4;
            trymove( map, movables );
            if( !moving()) {
                direction() = ( direction() + 2 ) % 4;
                trymove( map, movables );
            }
        }
    }
    if( !moving()) randomai( delta, map, movables );
}

void NPC::hit( Movable *hit, Map &map, vector<Movable *> &movables )
{
    if( ZOMBIE_MALE_TYPE <= type() && type() <= ZOMBIE_FEMALE_TYPE ) {
        // is this a non-zombie npc?
        if( hit->type() < ZOMBIE_MALE_TYPE ) {
            if(hit->_mapbase.movable_id == 202)
            {
                engine->push( new StateEvent( *engine, engine->data.events[2603] ));
                engine->push( new StateEvent( *engine, engine->data.events[2602] ));
                engine->push( new StateEvent( *engine, engine->data.events[2601] ));
            } else if (hit->_mapbase.movable_id == 203) {
                engine->push( new StateEvent( *engine, engine->data.events[2607] ));
            } else if (hit->_mapbase.movable_id == 208) {
                engine->push( new StateEvent( *engine, engine->data.events[2605] ));
                engine->push( new StateEvent( *engine, engine->data.events[2604] ));
            }
            hit->type() += 10;
            hit->base( &(engine->data.movables[ hit->mutable_id() ] ));
            hit->mapbase().movable_id = hit->mutable_id();
            engine->data.playernode.exp += 100;
            engine->sfx.loadSound(zombiesfx[rand() % 6], zombieSound, false);
            zombieSound.Play();
            // put down blood
            for( IDX i = 0; i < 4; ++i ) {
                if( map( x(), y() ).static_id[i] < 100 ) {
                    map( x(), y() ).static_id[i] = blood[ rand() % 3 ];
                    break;
                }
            }

        }
    }
}

