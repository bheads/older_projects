 module src.main;

 import src.core;



 void main()
{   
    Core    core = new Core();

    with( core ) {
        win.makewindow( 512, 600 );
        gfx.screen = win.screen;
        win.settext( "Wormy", "Wormy" );

        sm.push( new Menu( sm, core, true, true ));

        while( !sm.empty ) {
            fps.update();
            fps.delayframerate( 32 );
    
            input.update();

            if( input.newevent && input.event.type == SDL_QUIT ) {
                break;
            }

            sm.update( fps.delta );

            gfx.clear();
            sm.draw( fps.delta );
            gfx.flip();
        }
    }

    core.release();

}

