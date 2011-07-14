module  src.main;

import  std.stdio;

import src.gameobjects;

/+
version( Windows )
{
import core.runtime;
import std.c.windows.windows;
extern (Windows)
int WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) { 
        _main();
        return( 0 );
    }
} else {
void main() { _main(); }
}+/
 
void main()
{
    debug writeln( "Ninja Vs. Zombie Pirate Fish!" );
    debug writeln( "DEBUG MODE ENABLED!" );

    auto go = new GameObjects();

    with( go ) {

        win.makewindow( 512, 512 );
        gfx.screen = win.screen;
        gm.load( ID_ICON, FN_ICON );
        win.settext( "Ninja Vs. Zombie Pirate Fish", "NVZPF" );
        win.seticon( gm( ID_ICON ));

        sm.push( new StateMainMenu( sm, go, true, true ));

        debug writeln( "\tEntering the main loop" );
        while( !sm.empty ) {
            //debug writeln( "\t\tGetting timing" );
            fps.update();
            fps.delayframerate(32);
            //debug writeln( "\t\tGetting the input state" );
            input.update();

            //debug writeln( "\t\tTesting for SQL_QUIT" );
            if( input.newevent && input.event.type == SDL_QUIT ) {
                break;
            }

            //debug writeln( "\t\tRunning update" );
            sm.update( fps.delta );
            //debug writeln( "\t\tClearing" );
            gfx.clear();
            //debug writeln( "\t\tRunning draw" );
            sm.draw( fps.delta );
            //debug writeln( "\t\tFliping" );
            gfx.flip();
        }

        debug writeln( "\t\tCleaing up game pbjects" );
        go.clear();
    }
}



