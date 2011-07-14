module  src.statemainmenu;

import  src.gameobjects;

class StateMainMenu
    : State
{

    this( StateManager sm, GameObjects go, bool draw, bool update )
    {
        super( sm, go, draw, update );
    }

    override
    void update( float delta )
    {
        with( go ) {
            if( input.keys[ SDLK_UP ] ) {
                selected = ID_MENU_NEW;
            }
            if( input.keys[ SDLK_DOWN ] ) {
                selected = ID_MENU_QUIT;
            }
            if( input.keys[ SDLK_RETURN ] ) {
               if( selected == ID_MENU_QUIT ) {
                    sm.pop;
               } else {
                    sm.push( new StateGame( sm, go, true, true ));
               }
            }

        }
    }

    override
    void draw( float delta )
    {
        with( go ) {
            gfx.clear( screen, null, 0x0000ff );
            gfx.blit( gm( ID_MENU_MAIN), null, screen, &rect( 0, 0, 0, 0 ));
            if( selected == ID_MENU_NEW ) {
                gfx.blit( gm( ID_MENU_NEW_ARROW), null, screen, &rect( 70, 50, 0, 0 ));
                gfx.blit( gm( ID_MENU_QUIT), null, screen, &rect( 50, 110, 0, 0 ));
            } else {
                gfx.blit( gm( ID_MENU_NEW), null, screen, &rect( 50, 50, 0, 0 ));
                gfx.blit( gm( ID_MENU_QUIT_ARROW), null, screen, &rect( 70, 110, 0, 0 ));
            }
        }
    }

    override
    void enter()
    {
        with( go ) {
            gm.load( ID_MENU_NEW, FN_MENU_NEW );
            gm.load( ID_MENU_NEW_ARROW, FN_MENU_NEW_ARROW );
            gm.load( ID_MENU_QUIT, FN_MENU_QUIT );
            gm.load( ID_MENU_QUIT_ARROW, FN_MENU_QUIT_ARROW );
            gm.load( ID_MENU_MAIN, FN_MENU_MAIN );
        }
    }

    override
    void exit()
    {
        with( go ) {


        }
    }

    private:
        uint selected = ID_MENU_NEW;
}


