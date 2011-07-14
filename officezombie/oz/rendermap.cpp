

#include "rendermap.h"


void RenderMap::clear()
{
    msg( "Clearing render map" );
    for( IDX i = 0; i < npclist.size(); ++i ){
        delete npclist[i];
        npclist[i] = NULL;
    };

    for( IDX i = 0; i < boxlist.size(); ++i ){
        delete boxlist[i];
        boxlist[i] = NULL;
    };

    for( IDX i = 0; i < puzzlelist.size(); ++i ){
        delete puzzlelist[i];
        puzzlelist[i] = NULL;
    };

    for( IDX i = 0; i < eventlist.size(); ++i ){
        delete eventlist[i];
        eventlist[i] = NULL;
    };

    boxlist.clear();
    npclist.clear();
    puzzlelist.clear();
    eventlist.clear();
    movables.clear();
    map = NULL;
}

void RenderMap::build( Map &_map )
{
    F32 wx = 0.0f, wy = 0.0f, ly = 0.0f;
    clear();
    map = &_map;
    enforce( map != NULL, "No map pointer!" );
    enforce( map->Loaded(), "Map not loaded, cannot render from it" );

    movables.push_back( &player );
    // build NPC list
    for( IDX i = 0; i < map->npcs.size(); ++i ) {
        if(  map->npcs[i].type == EVENT_TYPE ) {
            eventlist.push_back( new EventObj( engine,
                        &(engine.data.movables[ map->npcs[i].movable_id ]), map->npcs[i] ));
            movables.push_back( eventlist.back());
        } else if(  map->npcs[i].type < CHAIR_TYPE ) {
            npclist.push_back( new NPC( engine,
                        &(engine.data.movables[ map->npcs[i].movable_id ]), map->npcs[i] ));
            movables.push_back( npclist.back());
        } else if( map->npcs[i].type < PUZZLE_TYPE ) {
            boxlist.push_back( new Box( engine,
                        &(engine.data.movables[ map->npcs[i].movable_id ]), map->npcs[i] ));
            movables.push_back( boxlist.back());
        }
        else if( map->npcs[i].type < EVENT_TYPE ) {
            puzzlelist.push_back( new Puzzle( engine,
                        &(engine.data.movables[ map->npcs[i].movable_id ]), map->npcs[i] ));
            movables.push_back( puzzlelist.back());
        }
    }
}

void RenderMap::update( F32 delta )
{
    // update boxes
    for( IDX i = 0; i < movables.size(); ++i ) {
        movables[i]->ai( delta, *map, movables );
        movables[i]->update( delta );
    }
}


// draw dimond in (x1, y1)->(x2, y2) centered around map ox,oy
void RenderMap::draw( I32 ox, I32 oy, I32 xw, I32 yw, F32 x1, F32 y1 )
{
    Sprite s, p;
    I32 sx, ex, sy, ey;
    F32 wx, wy, hw, hh;
    U32 hash;

    s.SetImage( engine.images.get( engine.data.tiles[ (*map)( ox, oy ).tile_id ].hash ));

    // compute x range around ox
    sx = ox - xw / 2;
    ex = ox + xw / 2;
    if( ex >= map->Width()) sx -= ex -( map->Width() - 1 );
    if( sx < 0 ) {
        ex -= sx;
        sx = 0;
    }
    if( ex >= map->Width()) ex = map->Width() - 1;

    // compute y range around oy
    sy = oy - yw / 2;
    ey = oy + yw / 2;
    if( ey >= map->Height()) sy -= ey -( map->Height() - 1 );
    if( sy < 0 ) {
        ey -= sy;
        sy = 0;
    }
    if( ey >= map->Height()) ey = map->Height() - 1;

    // fill out hw hh
    hw = s.GetSize().x / 2.0f;
    hh = s.GetSize().y / 2.0f;

    // update widths
    xw = ex - sx;
    yw = ey - sy;

    // need to computer the negative Y displacement then add y1 to it
    y1 = -(( 0 * hh ) - ( xw * hh )) + y1;

    for( I32 y = 0; y <= yw; ++y ) {
        for( I32 x = xw; x >= 0; --x ) {
            // draw floor tile
            hash =  engine.data.tiles[ (*map)( sx + x, sy + y ).tile_id ].hash;
            s.SetImage( engine.images.get( hash ));
            wx = x1 + ( x * hw ) + ( y * hw );
            wy = y1 + ( y * hh ) - ( x * hh );
            s.SetPosition( wx, wy );
            engine.gfx.Draw( s );
        }
    }

    for( I32 y = 0; y <= yw; ++y ) {
        for( I32 x = xw; x >= 0; --x ) {
            wx = x1 + ( x * hw ) + ( y * hw );
            wy = y1 + ( y * hh ) - ( x * hh );
            // draw static objects
            for( IDX i = 0; i < 4; ++ i ) {
                if( (*map)( sx + x, sy + y ).static_id[i] >= GD_STATIC_ID_MIN &&
                        !engine.data.static_objs[
                        (*map)( sx + x, sy + y ).static_id[i] ].draw_order ) {
                    hash = engine.data.static_objs[ (*map)( sx + x, sy + y ).static_id[i] ].hash;
                    p.SetImage( engine.images.get( hash ));
                    p.SetPosition( wx, wy - p.GetSize().y + s.GetSize().y );
                    engine.gfx.Draw( p );
                }
            }

            // draw moveables
            for( IDX i = 0; i < movables.size(); ++i ) {
                if( movables[i]->moving() && movables[i]->offset() >= 0.5f) {
                    if(( sx + x ) == movables[i]->x() &&
                            ( sy + y ) == movables[i]->y()) {
                        movables[i]->draw( x1, y1, x + movables[i]->xoffset(),
                                y + movables[i]->yoffset(), hw, hh );
                    }
                } else {
                    if(( sx + x ) == movables[i]->rx() &&
                            ( sy + y ) == movables[i]->ry()) {
                        if( CHAIR_TYPE <= movables[i]->type() &&
                                movables[i]->type() <= DESK_TYPE ) {
                            if( player.level() > (movables[i]->type() - CHAIR_TYPE )) {
                                p.SetImage( engine.images.get( player.green()));
                            } else {
                                p.SetImage( engine.images.get( player.red()));
                            }
                            p.SetPosition( wx, wy );
                            engine.gfx.Draw( p );
                        }
                        movables[i]->draw( x1, y1, x, y, hw, hh );
                    }
                }
            }

            for( IDX i = 0; i < 4; ++ i ) {
                if( (*map)( sx + x, sy + y ).static_id[i] >= GD_STATIC_ID_MIN &&
                        engine.data.static_objs[
                        (*map)( sx + x, sy + y ).static_id[i] ].draw_order ) {
                    hash = engine.data.static_objs[ (*map)( sx + x, sy + y ).static_id[i] ].hash;
                    p.SetImage( engine.images.get( hash ));
                    p.SetPosition( wx, wy - p.GetSize().y + s.GetSize().y );
                    engine.gfx.Draw( p );
                }
            }
        } // for x
    } // for y
}
