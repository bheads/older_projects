module  src.gameobjects;

public
import     std.random,
            std.stdio;

public
import     src.graphics,
            src.input,
            src.state,
            src.statemanager,
            src.graphicsmanager,
            src.window,
            src.fps,
            src.camera,
            src.gameworld,
            src.staticobject, 
            src.dynamicobject,
            src.eventobject,
            src.aiobject,
            src.ninja,
            src.sdl;

public
import     src.statemainmenu,
            src.stategame,
            src.statepause,
            src.stategotstars,
            src.statedead,
            src.statestageexit;


class GameObjects
{
    this()
    {
        win = new Window();
        input = new Input();
        gfx = new Graphics();
        gm = new GraphicsManager( gfx );
        sm = new StateManager();
        fps = new FPS();
    }

    void clear()
    {
        debug writeln( "\t\t\tsm.clear" );
        sm.clear();
        debug writeln( "\t\t\tgm.clear" );
        gm.clear();
        debug writeln( "\t\t\twin.closewindow" );
        win.closewindow();
    }

    @property surface screen() { return gfx.screen; }

    Window          win;
    Input           input;
    Graphics        gfx;
    GraphicsManager gm;
    StateManager    sm;
    FPS             fps;
    onHit[]         hf;
    onHitAI[]       ahf;
    onUpdateAI[]    auf;
}

