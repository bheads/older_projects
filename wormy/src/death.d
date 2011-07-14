module  src.death;

import  std.conv;

import  src.core;

class Death
    : State
{
    ulong score;

    this( StateManager sm, Core core, bool draw, bool update, ulong score )
    {
        super( sm, core, draw, update );
        this.score = score;
    }

    override
    void update( float delta )
    {
        with( core ) {
            if( input.keys[ SDLK_ESCAPE ] ) {
                sm.pop();
                sm.pop();
            }
            if( input.mouse.btn ) {
                sm.pop();
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

            surface scoresurf = gfx.gettext( text("You Died! SCORE: ", score ), 0x22, 0x22, 0x22 );
            gfx.blit( scoresurf, null, gfx.screen, &rect( 160, 230, 0, 0 ));
            SDL_FreeSurface( scoresurf );
        }
    }

    override
    void enter()
    {
        with( core ) {
        }
    }

    override
    void exit()
    {
        with( core ) {


        }
    }

}


