module  src.input;

import  std.stdio;

import  src.sdl;


struct Mouse
{
    byte    btn;
    int     x, y;
    int     ox, oy;
}

class Input
{
    public:
        


        void update()
        {
            keys = SDL_GetKeyState( null );
            //debug writeln( "\t\t\tGetting Relative State" );
            mouse.btn = SDL_GetRelativeMouseState( &mouse.ox, &mouse.oy );
            //debug writeln( "\t\t\tGetting Abs State" );
            SDL_GetMouseState( &mouse.x, &mouse.y );
            //debug writeln( "\t\t\tGetting Event" );
            newevent = ( SDL_PollEvent( &event ) == 1 ? true : false );
        }

        ubyte*      keys;
        Mouse       mouse;
        SDL_Event   event;
        bool        newevent;
}




