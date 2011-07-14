module  src.stategame;

import  std.math;


import  src.gameobjects;


class StateGame
    : State
{

    this( StateManager sm, GameObjects go, bool draw, bool update )
    {
        super( sm, go, draw, update );
        
        // setup list of event functions           
        go.hf ~= &smallgold; //0
        go.hf ~= &gold; //1
        go.hf ~= &largegold; //2
        go.hf ~= &hugegold; //3
        go.hf ~= &gotstars; //4
        go.hf ~= &seaweed; //5
        go.hf ~= &stageexit; //6
        
        go.ahf ~= &hitfish;
        go.auf ~= &updatefish;
        go.ahf ~= &hitstar;
        go.auf ~= &updatestar;
        
        gw = new GameWorld( 0, 0, 2048, 768, 0 );
        gw.load( go, "lvls/stag1.txt" );
        
        ninja = new Ninja( gw.nx, gw.ny, 64, 64, ID_NINJA_DOWN );
        ninja.setbounds( 0, 0, cast(short)(gw.w-32), cast(short)(gw.h-32));
        gw.dy ~= ninja;
        
        cam = new Camera( 0, 0, 512, 512, 0 );
        cam.setbounds( 0, 0, cast(short)(gw.w-512), cast(short)(gw.h-498));
    }

    override
    void update( float delta )
    {
        if( ic > 0 ) --ic;
        with( go ) {
           if( input.keys[ SDLK_p ] ) {
                sm.push( new StatePause( sm, go, true, false ));
                SDL_Delay( 200 );
                fps.update();
                return;
            }
            
            // reset key
            if( input.keys[ SDLK_r ] ) {
                ninja.set( gw.nx, gw.ny );
                SDL_Delay( 200 );
            }
            
            if( input.keys[ SDLK_ESCAPE] ) {
                sm.pop;
                return;
            }
            
            // update ninja
            {
            float a = 10.0, ax = 0.0, ay = 0.0;
            if( input.keys[ SDLK_UP ] ) ay = -a;
            if( input.keys[ SDLK_DOWN ] ) ay = a;
            if( input.keys[ SDLK_LEFT ] ) ax = -a;
            if( input.keys[ SDLK_RIGHT ] ) ax = a;
            ninja.update( delta, ax, ay );
            }
            
            // throwing stars
            if( ninja.hasstars && ninja.stars > 0 ) {     
                if( input.keys[ SDLK_SPACE ] && ic == 0 ) {
                    ic = 20;
                    gw.ai ~= new AIObject( cast(short)(ninja.x + ninja.w/2),
                                            cast(short)(ninja.y + ninja.h/2),
                                            24, 24, 
                                            ID_NINJA_STARS[ ninja.star ],
                                            ahf[1], auf[1] );
                    switch( ninja.id ) {
                        case ID_NINJA_RIGHT:
                            gw.ai[$-1].dir = 1;
                            break;
                        case ID_NINJA_DOWN:
                            gw.ai[$-1].dir = 2;
                            break;
                        case ID_NINJA_LEFT:
                            gw.ai[$-1].dir = 3;
                            break;
                        case ID_NINJA_UP:
                        default:
                            gw.ai[$-1].dir = 4;
                            break;
                    }
                }   
            }
          
          
            // update badies!
            foreach( ai; gw.ai ) {
                if( !ai.alive ) continue;
                bool found = false;
                ai.updateai( delta );
                foreach( s; gw.st ) {
                    if( ai.boxtest( s )) {
                        if( ai.pixeltest( go, cam, s )) {
                            found = true;
                        } 
                    }
                }
                if( found ) {
                    ai.reject( delta );
                } else {
                    ai.accept();
                }
            }// ai update
            
            foreach( a; gw.ai ) {
                foreach( b; gw.ai ) {
                    if( a is b ) continue;
                    if( !a.alive || !b.alive ) continue;
                    if( a.boxtest( b )) {
                        if( a.pixeltest( go, cam, b )) {
                            a.event( b );
                        }
                    }
                }
            }
          
            // collision detection
            foreach( dobj;  gw.dy ) {
                if( !dobj.alive ) continue;
                foreach( eobj; gw.ev ) {
                    if( eobj._hit is null ) continue;
                    if( dobj.boxtest( eobj )) {
                        if( dobj.pixeltest( go, cam, eobj )) {
                            eobj.event( dobj );
                        }
                    }
                 } //foreach event object
                         
                
                bool found = false;
                foreach( sobj; gw.st ) {
                    if( dobj.boxtest( sobj )) {
                        if( dobj.pixeltest( go, cam, sobj )) {
                            found = true;
                        } 
                    }
                }
                if( found ) {
                    dobj.reject( delta );
                } else {
                    dobj.accept();
                }//foreach static                
                
                foreach( ai; gw.ai ) {
                    if( dobj.boxtest( ai )) {
                        if( dobj.pixeltest( go, cam, ai )) {
                            ai.event( dobj );
                        }
                    }
                 } //foreach ai object
                
            }//foreach
                    
            foreach( dobj;  gw.dy ) {
                if( dobj.nodamage > 0 ) --dobj.nodamage;
            }
            
            if( ninja._life == 0 ) {
                sm.push( new StateDead( sm, go, true, false ));
                return;
            }
                    
            cam.center( ninja );
            cam.update();
            cam.accept();
        }
    }


    override
    void draw( float delta )
    {
        with( go ) {
            gfx.clear( screen, null, 0xff - cast(uint)((ninja.y)/3.5) );
            // draw statics
            foreach( s; gw.st ) {
                if( !s.alive ) continue;
                if( cam.boxtest( s )) {
                    gfx.blit( gm( s.id ), null, screen, &rect( cast(short)(s.x - 
                            cam.x), cast(short)(s.y - cam.y), 0 , 0 ));
                }
            }
            // draw event objects
            foreach( e; gw.ev ) {
                if( !e.alive ) continue;
                if( cam.boxtest( e )) {
                    gfx.blit( gm( e.id ), null, screen, &rect( cast(short)(e.x - 
                            cam.x), cast(short)(e.y - cam.y), 0 , 0 ));
                }
            }
            
            // draw ai objects
            foreach( ai; gw.ai ) {
                if( !ai.alive ) continue;
                if( cam.boxtest( ai )) {
                    gfx.blit( gm( ai.id ), null, screen, &rect( cast(short)(ai.x - 
                            cam.x), cast(short)(ai.y - cam.y), 0 , 0 ));
                }
            }
            
            
            // Draw Ninja
            gfx.blit( gm( ninja.id), null, screen, &rect( 
         cast(short)(ninja.x - cam.x), cast(short)(ninja.y - cam.y), 0 , 0 ));
         debug writeln( ninja.x, " ", ninja.y );
                
             debug 
             foreach( dobj;  gw.dy ) {
                if( !dobj.alive ) continue;
                foreach( sobj; gw.st ) {
                    if( dobj.boxtest( sobj )) {
                        dobj.cbox( go, cam, sobj );
                        dobj.pixeltest( go, cam, sobj );
                    }
                }
            } //foreach
  
            // draw hud
            gfx.blit( gm( ID_HUD_LIFE ), null, screen, &rect( 5, 5, 0, 0 ));
            foreach( i; 0..ninja._life ) {
                 gfx.blit( gm( ID_HUD_HEARTS[i] ), null, screen, 
                    &rect( cast(short)(65 + 32 * i), 5, 0, 0 ));
            }
            
            if( ninja.hasstars && ninja.stars > 0 ) {
                gfx.blit( gm( ID_NINJA_STARS[ninja.stars-1]), null, screen,
                    &rect( 480, 5,0,0));
            }
            
        }//with        
    }//draw

    override
    void enter()
    {
        StopDraw = true;
        StopUpdate = true;
        with( go ) {
            gm.load( ID_NINJA_UP, FN_NINJA_UP );
            gm.load( ID_NINJA_DOWN, FN_NINJA_DOWN );
            gm.load( ID_NINJA_LEFT, FN_NINJA_LEFT );
            gm.load( ID_NINJA_RIGHT, FN_NINJA_RIGHT );
            
            foreach( i, id; ID_NINJA_STARS ) {
                gm.load( id, FN_NINJA_STARS[i] );
            }

            gm.load( ID_HUD_LIFE, FN_HUD_LIFE );            
            foreach( i, id; ID_HUD_HEARTS ) {
                gm.load( id, FN_HUD_HEARTS[i] );
            }

        }
    }

    override
    void exit()
    {
        with( go ) {
            hf.length = 0;
            ahf.length = 0;
            auf.length = 0;
        }
    }
    
    //0
    void smallgold( DynamicObject o, EventObject e ) 
    {
        if( o is ninja ) {
            e.alive = false;
            ninja.money = 100;
        }
    }
    
    //1
    void gold( DynamicObject o, EventObject e ) 
    {
        if( o is ninja ) {
            e.alive = false;
            ninja.money = 250;
        }
    }
    
    //2
    void largegold( DynamicObject o, EventObject e ) 
    {
        if( o is ninja ) {
            e.alive = false;
            ninja.money = 500;
        }
    }
    
    //3
    void hugegold( DynamicObject o, EventObject e ) 
    {
        if( o is ninja ) {
            e.alive = false;
            ninja.money = 1000;
        }
    }
    
    //4
    void gotstars( DynamicObject o, EventObject e ) 
    {
        if( o is ninja ) {
            ninja.money = 50;
            ninja.hasstars = true;
            e.id = 1;
            e._hit = null;
            sm.push(new StateGotStars( sm, go, true, false ));
            debug writeln ( "NINJA Found Stars!" );
        }
    }
    
    //5 seaweed
    void seaweed( DynamicObject o, EventObject e )
    {
        if( o is ninja && ninja.nodamage == 0 ) {
            --ninja._life;
            ninja.nodamage = 32;
        }
    }
    
    void stageexit( DynamicObject o, EventObject e )
    {
        if( o is ninja ) {
            ninja.money = ninja._life * 100;
            ninja.money = ninja.stars * 10;
            sm.push(new StateStageExit( sm, go, true, false, ninja.money ));
        }
    }

    // #0 ahf
    void hitfish( DynamicObject d, AIObject a )
    {
        if( !a.alive || !d.alive) return;
        if( d is ninja  && ninja.nodamage == 0 ) {
            --ninja._life;
            ninja.nodamage = 32;        
        }
    }
    
    // #1ahf
    void hitstar( DynamicObject s, AIObject a )
    {
        if( !a.alive || !s.alive) return;
        if( s !is ninja && s.id < ID_NINJA_STARS[0] ) {
            ninja.money = 100 * ( a.id >= 500 ? 5 : 1 ); 
            a.alive = false;
            --s._life;
            if( s._life <= 0 ) s.alive = false;
        }        
    }
    
    // #0 auf
    void updatefish( AIObject a, float delta )
    {   
        if( a.first ) {
            a.update( delta, -6.0, 0.0 );
            a.count = 98;
            a.first = false;
            if( a.id  == 500 ) {
                a._life = 8;
            }
        } else {
            if( go.gfx.dist( ninja, a ) <= 300.0 ) {
                float ax = ninja.x - a.x, ay = ninja.y - a.y;
                if( ax > 5.0 ) ax = 5.0;
                if( ay > 5.0 ) ay = 5.0;
                if( ax < -3.0 ) ax = -3.0;
                if( ay < -3.0 ) ay = -3.0;
                a.update( delta, ax, ay );
                
                if( a.vx > 0.0 && a.dir == 1 ) {
                    ++a._fid;
                    a.dir = 2;
                } else if( a.vx < 0.0 && a.dir != 1 ) {
                    --a._fid;
                    a.dir = 1;
                }
                
            } else {
                --a.count;
                if( a.count <= 0 ) {
                    if( a.dir == 1 ) {
                        a.dir = 2;
                        ++a._fid;               
                    } else {
                        a.dir = 1;
                        --a._fid;
                    }
                    a.count = 98;         
                }
                
                if( a.dir == 1 ) a.update( delta, -3.0, 0.0 );
                else  a.update( delta, 5.0, 0.0 );
           }
        }        
    }
    
    // #1 auf
    void updatestar( AIObject a, float delta )
    {
        switch( a.dir ) {
            case 1:
                a.update( delta, 16.0, 0.0 );
                break;
            case 2:
                a.update( delta, 0.0, 16.0 );
                break;
            case 3:
                a.update( delta, -12.0, 0.0 );
                break;
            case 4:
            default:
                a.update( delta, 0.0, -12.0 );
                break;    
        }
    }

    private:
        GameWorld   gw;
        Ninja       ninja;
        Camera      cam;
        
        int         ic = 0;
        
        

}


