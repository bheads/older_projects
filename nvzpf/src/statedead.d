module  src.statedead;

import  src.gameobjects;

class StateDead
    : State
{

    this( StateManager sm, GameObjects go, bool draw, bool update )
    {
        super( sm, go, draw, update );
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
            gfx.blit( gm(ID_MENU_DEAD), null, screen,
                &rect( 256 - 128, 256-64,0,0));
        }
    }

    override
    void enter()
    {
        StopDraw = false;
        StopUpdate = true;
        with( go ) {
           gm.load( ID_MENU_DEAD, FN_MENU_DEAD );
        }

    }

    override
    void exit()
    {
    }
    
    int count   = 200;

}


