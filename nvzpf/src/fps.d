module  src.fps;

import  std.conv;

import  src.gameobjects;


enum SEC = 1_000U;
enum DSEC = 1_000.0;

class FPS
{

    this()
    {
        lasttick = SDL_GetTicks();
    }

    void update()
    {
        uint tmp = SDL_GetTicks();
        ++fpscount;
        _idelta = tmp - lasttick;
        _delta = _idelta / DSEC;
        tickcount += _idelta;

        if( tickcount >= SEC ) {
            _fps = fpscount;
            tickcount = 0;
            fpscount = 0;
            debug writeln( "FPS: ", _fps, "  ", _delta, "  ", _idelta );
        }

        lasttick = tmp;
    }

    void delayframerate( int rate = 32 )
    {
        uint delaydelta =  SEC / rate;
        int delay = delaydelta - _idelta;
        if( delay > 0 ) {
            SDL_Delay( delay );
        }

    }

    @property int fps() { return _fps; }
    @property string fps() { return to!string(_fps); }
    @property uint idelta() { return _idelta; }
    @property float delta() { return _delta; }

    private:
        uint    lasttick;
        uint    tickcount;
        int     _fps, fpscount;
        uint    _idelta;
        float  _delta;


}

