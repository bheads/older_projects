

#include "player.h"

//ugly hard coded stuff. 7 zombie sound effects in an array to be used with a rand()
U32 zombiesfx[7] = {1113142547, 1118531726, 1123726330, 1129315253, 1126054081, 1139572060, 1136508456};

U32 blood[] = { 113, 114, 115, 115, 114, 113 };

bool Player::trypull( Direction dir, Map &map, vector<Movable*> &movables )
{
    Movable *box;
    if( engine.input.keys[ Key::Space ].down && direction() != dir ) {
        if(( box = infront( map, movables )) != NULL &&
                (( CHAIR_TYPE <= box->type() && box->type() <= DESK_TYPE &&
                level() > ( box->type() - CHAIR_TYPE )) ||
                ( ZOMBIE_MALE_TYPE <= box->type() && box->type() <=
                  ZOMBIE_FEMALE_TYPE))){
            rdir = direction();
            restore = true;
            direction( dir );
            trymove( map, movables );
            if( moving()) {
                box->direction( direction());
                box->trymove( map, movables );
                // test if there is a wall or block between future position
                if( !box->moving()) {
                    x( rx());
                    y( ry());
                    moving( 0 );
                } else {
                    if( map( x(), y()).block & block_dir[ rdir ] ||
                            map( box->x(), box->y()).block & block_rdir[ rdir ] ) {
                        x( rx());
                        y( ry());
                        moving( 0 );
                        box->moving( 0 );
                        box->x( box->rx());
                        box->y( box->ry());
                    }
                }
            }
            return true;
        }
    }
    return false;
}

void Player::ai( F32 delta, Map &map, vector<Movable*> &movables )
{
    Movable *box;
    if( !moving()) {
        if( restore ) {
            direction( rdir );
            restore = false;
        }

        if( engine.input.keys[ Key::Left ].down ) {
            if( !trypull( West, map, movables)) {
                direction( West );
                if( !engine.input.shift ) {
                    trymove( map, movables );
                }
            }
        } else if( engine.input.keys[ Key::Right ].down ) {
            if( !trypull( East, map, movables )) {
                direction( East );
                if( !engine.input.shift ) {
                    trymove( map, movables );
                }
            }
        } else if( engine.input.keys[ Key::Up ].down ) {
            if( !trypull( North, map, movables )) {
                direction( North );
                if( !engine.input.shift ) {
                    trymove( map, movables );
                }
            }
        } else if( engine.input.keys[ Key::Down ].down ) {
            if( !trypull( South, map, movables )) {
                direction( South );
                if( !engine.input.shift ) {
                    trymove( map, movables );
                }
            }
        }
        if( moving() ) {
            cout << "@ " << x() << "x" << y() << endl;
        }
    }
}

void Player::hit( Movable *hit, Map &map, vector<Movable*> &movables )
{
    // is this a non-zombie npc?
    if( hit->type() < ZOMBIE_MALE_TYPE ) {
        if(hit->_mapbase.movable_id == 202)
        {
            engine.push( new StateEvent( engine, engine.data.events[2603] ));
            engine.push( new StateEvent( engine, engine.data.events[2602] ));
            engine.push( new StateEvent( engine, engine.data.events[2601] ));
        } else if (hit->_mapbase.movable_id == 203) {
            engine.push( new StateEvent( engine, engine.data.events[2607] ));
        } else if (hit->_mapbase.movable_id == 208) {
            engine.push( new StateEvent( engine, engine.data.events[2605] ));
            engine.push( new StateEvent( engine, engine.data.events[2604] ));
        }
        hit->type() += 10;
        hit->base( &(engine.data.movables[ hit->mutable_id() ] ));
        hit->mapbase().movable_id = hit->mutable_id();
        exp( exp() + 125 );
        engine.sfx.loadSound(zombiesfx[rand() % 6], zombieSound, false);
        zombieSound.Play();

        // put down blood
        for( IDX i = 0; i < 4; ++i ) {
            if( map( x(), y() ).static_id[i] < 100 ) {
                map( x(), y() ).static_id[i] = blood[ rand() % 3 ];
                break;
            }
        }

    } else if(( CHAIR_TYPE <= hit->type() && hit->type() <= DESK_TYPE &&
            !restore && level() > ( hit->type() - CHAIR_TYPE ))) {
        hit->direction( direction());
        hit->trymove( map, movables );
        if( hit->moving()) {
            trymove( map, movables, false );
        }
    } else if( ZOMBIE_MALE_TYPE <= hit->type() && hit->type() <= ZOMBIE_FEMALE_TYPE ) {
        if( engine.input.keys[ Key::Space ].down && !hit->moving()) {
            hit->direction( direction());
            hit->trymove( map, movables );
            if( hit->moving()) {
                trymove( map, movables, false );
            }
        } else if( engine.input.keys[ Key::A ].down ) {
            hit->alive() = 0;
            engine.sfx.loadSound(zombiesfx[rand() % 6], zombieSound, false);
            zombieSound.Play();
            // put down blood
            for( IDX i = 0; i < 4; ++i ) {
                if( map( x(), y() ).static_id[i] < 100 ) {
                    map( x(), y() ).static_id[i] = blood[ rand() % 3 ];
                    break;
                }
            }
        } else {
            if( !hit->moving()) {
                trymove( map, movables, false );
                hit->direction( rdirection[ direction() ]);
                hit->trymove( map, movables, false );
            }
        }
    } else if( hit->type() == PUZZLE_TYPE ) {
        // hit Puzzle Block
        changemap( engine.data.puzzles[ hit->mapbase().mutable_id ] );
    } else if( hit->type() == EVENT_TYPE ) {
        // hit Event Block
        runevent( engine.data.events[ hit->mapbase().mutable_id ] );
        hit->alive(false);
    }

}

Movable *Player::infront( Map &map, vector<Movable*> &movables )
{
    I32 fx = x(), fy = y();
    switch( direction()) {
        case North:
            fy--;
            break;
        case East:
            fx++;
            break;
        case South:
            fy++;
            break;
        case West:
            fx--;
    }
    for( IDX i = 0; i < movables.size(); ++i ) {
        if( movables[i]->x() == fx &&
                movables[i]->y() == fy &&
                movables[i]->alive()) {
            // test for map blocked
            if( map( x(), y()).block & block_dir[ direction() ] ||
                    map( fx, fy ).block & block_rdir[ direction() ] ) {
                return NULL;
            } else {
                return movables[i];
            }
        }
    }
    return NULL;
}


F32 Player::scale()
{
    F32 s = ( (F32)exp() / (F32)max_exp());
    if( s < 0.001f ) s = 0.001f;
    return s;
}

void Player::changemap( PuzzleNode &puzzle )
{
    if( puzzle.solved ) {
        map_id( puzzle.map_id );
        rx( x( puzzle.x ));
        ry( y( puzzle.y ));
        moving( 0 );
        direction( puzzle.direction );
    } else {
        engine.push( new StatePuzzle( engine, puzzle ));
    }
}

void Player::runevent( EventNode &event )
{
    engine.push( new StateEvent( engine, event ));
}

