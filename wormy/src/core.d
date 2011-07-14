
module src.core;

public
import  std.random,
        std.stdio;


public 
import  src.sdl,
        src.window,
        src.sound,

        src.state,
        src.statemanager,
        src.menu,
        src.game,
        src.pause,
        src.death,

        src.worm,

        src.fps,

        src.graphics,

        src.input;




class Core
{
    this()
    {
        win = new Window();
        input = new Input();
        gfx = new Graphics();
        fps = new FPS();
        sound = new Sound();
        sound.load( "crash.ogg" );

        sm = new StateManager();
    }


    void release()
    {
        debug writeln( "core is clearing statemanger" );
        sm.clear();

        debug writeln( "core is closing window" );
        win.closewindow();
    }

    @property surface screen() { return gfx.screen; }

    Window          win;
    StateManager    sm;
    FPS             fps;
    Graphics        gfx;
    Input           input;
    Sound           sound;

}

