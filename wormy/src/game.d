module  src.game;

import  std.conv;

import  src.core;

class Game
    : State
{

    float updatetimer = 0.0f, updaterate = 1.0f / 15.0f;
    bool left = false, right = false, plus = false, minus = false;
    float spacedelay = 0.0f;
    bool buildup = false, alive = true;;
    uint checkboxdelay = 0;
    ulong score = 0;

    this( StateManager sm, Core core, bool draw, bool update )
    {
        super( sm, core, draw, update );
    }

    override
    void update( float delta )
    {
        with( core ) {

            // keys
            if( input.keys[ SDLK_RIGHT ] ) {
                if( !right ) {
                    worms[0].dir++;
                    if( worms[0].dir > 3 ) worms[0].dir = 0;
                }
                right = true;
            } else {
                right = false;
            }
            
            if( input.keys[ SDLK_LEFT ] ) {
                if( !left ) {
                    worms[0].dir--;
                    if( worms[0].dir < 0 ) worms[0].dir = 3;
                }
                left = true;
            } else {
                left = false;
            }

            if( input.keys[ SDLK_EQUALS ] ) {
                if( !plus ) {
                    updaterate *= 0.90f;
                    debug writeln( "new rate: ", updaterate );
                }
                plus = true;
            } else {
                plus = false;
            }

            if( input.keys[ SDLK_MINUS ] ) {
                if( !minus ) {
                    updaterate *= 1.10f;
                    debug writeln( "new rate: ", updaterate );
                }
                minus = true;
            } else {
                minus = false;
            }

            spacedelay -= delta;
            if( input.keys[ SDLK_SPACE ] ) {
                if( spacedelay <= 0.0f ) {
                    sm.push( new Pause( sm, core, false, true ));
                    spacedelay = 0.20f;
                }
            }

            if( spacedelay <= 0.0f && input.keys[ SDLK_ESCAPE ]) {
                sm.pop;
            }
    
            gfx.box( gfx.screen, 12, 524, 12, 12, 0xaaaaaa00 );
            if( input.mouse.btn &&
                    ( 12 <= input.mouse.x && input.mouse.x <= 24 ) &&
                    ( 524 <= input.mouse.y && input.mouse.y <= 536 )) {
                ++checkboxdelay;
                if( checkboxdelay >= 5 ) {
                    buildup = !buildup;
                    checkboxdelay = 0;
                }
            }else {
                checkboxdelay = 0;
            }


            updatetimer += delta;
            if( updatetimer >= updaterate ) {
                if( buildup ) {
                    updaterate *= 0.9995;
                }
                if( updaterate < 1.0f/60.0f ) updaterate = 1.0f/60.0f;
                
                // ai, logic
                updatetimer = 0.0f;
                foreach( i, ref worm; worms ) {
                    if( i != 0 ) {
                        worm.ai( worms );
                    } else {
                        if( worm.crashtest( worms )) {
                            alive = false;
                            sm.push( new Death( sm, core, false, true, score ));
                            sound.play();
                        }
                    }
                    worm.update( worms );
                }
                if( alive ) {
                    score += worms[0]._body.length;
                }
            }

        }
    }

    override
    void draw( float delta )
    {
        with( core ) {
            // draw background
            for( short y = 0; y < 50; ++y ) {
                for( short x = 0; x < 50; ++x ) {
                    gfx.box( gfx.screen, 
                            cast(short)(( x * width ) + offset + 1),
                            cast(short)(( y * height ) + offset + 1),
                            width - 2, height - 2, 0x22222200 );
                }
            }

            // bottom bars
            gfx.box( gfx.screen, 6, 512, 500, 82, 0x22222200 ); 
            gfx.box( gfx.screen, 12, 524, 12, 12, 0xaaaaaa00 );
            gfx.box( gfx.screen, 13, 525, 10, 10, 0x22222200 );
            if( buildup ) {
                gfx.box( gfx.screen, 14, 526, 8, 8, 0xaaaaaa00 );
            }
            gfx.blit( checktext, null, gfx.screen, &rect( 26, 519, 0, 0 ));


            scoresurf = gfx.gettext( text("SCORE: ", score ), 0xaa, 0xaa, 0xaa );
            gfx.blit( scoresurf, null, gfx.screen, &rect( 200, 530, 0, 0 ));
            SDL_FreeSurface( scoresurf );

            // draws worms
            foreach( ref worm; worms ) {
                worm.draw();
            }
        }
    }

    override
    void enter()
    {
        with( core ) {
            foreach( i, ref worm; worms ) { 
                worm = new Worm( core );
                worm.spawn( i );
            }

            checktext = gfx.gettext( "Build up speed", 0xaa, 0xaa, 0xaa );
        }
    }

    override
    void exit()
    {
        with( core ) {
            SDL_FreeSurface( checktext );

        }
    }


    Worm[4]     worms;
    surface     checktext, scoresurf;
}


