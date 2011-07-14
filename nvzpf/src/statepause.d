module  src.statepause;

import  src.gameobjects;

   

class StatePause
    : State
{

    this( StateManager sm, GameObjects go, bool draw, bool update )
    {
        super( sm, go, draw, update );
        pause = new DynamicObject( 248 - 128,  248 - 32, 256, 64, ID_MENU_PAUSE );
        pause.setbounds( 0, 0, 512-256, 512-64 );
    }

    override
    void update( float delta )
    {
        with( go ) {
            if( input.keys[ SDLK_p ] ) {
                SDL_Delay( 200 );
                sm.pop();
                return;
            }
        }
        
        pause.update( delta, uniform( -10, 12 ), uniform( -10, 12 ));
        pause.accept();
                
    }

    override
    void draw( float delta )
    {
        with( go ) {
            gfx.blit( gm( ID_MENU_PAUSE ), null, screen, &rect( pause.x, pause.y, 0, 0 ));
        }
    }

    override
    void enter()
    {
        StopDraw = false;
        StopUpdate = true;
        with( go ) {
            gm.load( ID_MENU_PAUSE, FN_MENU_PAUSE );
        }
    }

    override
    void exit()
    {
        with( go ) {


        }
    }
    
    private:
        DynamicObject   pause;

}


