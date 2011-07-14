module  src.statestageexit;

import  std.conv;

import  src.gameobjects;

class StateStageExit
    : State
{

    this( StateManager sm, GameObjects go, bool draw, bool update, int score )
    {
        super( sm, go, draw, update );
        this.score = score;
    }

    override
    void update( float delta )
    {
        debug writeln( "update" );    
        with( go ) {
            --count;
            if( count <= 0 ) {
                sm.pop();
                sm.pop();
                return;
            }
        }
    }

    override
    void draw( float delta )
    {
        debug writeln( "draw" );
        with( go ) {
            gfx.blit( gm(ID_MENU_EXIT), null, screen,
                &rect( 256 - 128, 256-64,0,0));
            gfx.blit( surf, null, screen,
                &rect( 264, 250 ));
        }
    }

    override
    void enter()
    {
        StopDraw = false;
        StopUpdate = true;
        with( go ) {
           gm.load( ID_MENU_EXIT, FN_MENU_EXIT );
           surf = gfx.gettext( to!string( score ));
        }

    }

    override
    void exit()
    {
        SDL_FreeSurface( surf );
    }
    
    int count   = 200;
    int score;
    surface surf;

}


