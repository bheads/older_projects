module  src.pause;

import  src.core;

class Pause
    : State
{
    float keydelay = 0.20f;
    surface paused;

    this( StateManager sm, Core core, bool draw, bool update )
    {
        super( sm, core, draw, update );
    }

    override
    void update( float delta )
    {
        with( core ) {
            keydelay -= delta;
            if( keydelay <= 0.0f ) keydelay = 0.0f;

            if( keydelay <= 0.0f && input.keys[ SDLK_SPACE ] ) {
                sm.pop();
            }

            if( input.keys[ SDLK_ESCAPE ] ) {
                sm.pop();
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
            gfx.blit( paused, null, gfx.screen, &rect( 230, 238 ));
        }
    }

    override
    void enter()
    {
        with( core ) {
            paused = gfx.gettext( "PAUSED!", 0, 0, 0 );
        }
    }

    override
    void exit()
    {
        with( core ) {
            SDL_FreeSurface( paused );

        }
    }

}


