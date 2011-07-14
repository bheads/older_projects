module  src.menu;

import  src.core;

class Menu
    : State
{
    uint escape = 0, mousebtn = 0;

    this( StateManager sm, Core core, bool draw, bool update )
    {
        super( sm, core, draw, update );
    }

    override
    void update( float delta )
    {
        with( core ) {
            if( input.keys[ SDLK_ESCAPE ] ) {
                ++escape;
                if( escape > 6 ) {
                    sm.pop();
                }
            } else {
                escape = 0;
            }

            if( input.mouse.btn && 
                    ( 150 <= input.mouse.x && input.mouse.x <= 150+225 ) &&
                    ( 221 <= input.mouse.y && input.mouse.y <= 221+70 )) {
                ++mousebtn;
                if( mousebtn > 6 ) {
                    sm.push( new Game( sm, core, true, true ));
                    mousebtn = 0;
                }

            } else {
                mousebtn = 0;
            }

        }
    }

    override
    void draw( float delta )
    {
        with( core ) {
            gfx.box( gfx.screen, 150 -2, 221 - 2, 225+4 ,70+4, 0xffffff00 );
            gfx.box( gfx.screen, 150, 221, 225 + 2, 70+2, 0x33333300 );
            gfx.box( gfx.screen, 150, 221, 225 ,70, 0xaaaaaa00 );

            gfx.blit( start, null, gfx.screen, &rect( 160, 230, 0, 0 ));
        }
    }

    override
    void enter()
    {
        with( core ) {
            start = gfx.gettext( "PLAY!", 0x22, 0x22, 0x22 );
        }
    }

    override
    void exit()
    {
        with( core ) {
            SDL_FreeSurface( start );
        }
    }

    surface start;
}


