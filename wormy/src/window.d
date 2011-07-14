module  src.window;

import  std.stdio,
        std.string,
        std.conv,
        std.exception;

import  src.sdl;




class Window
{
    void makewindow( int x, int y )
    {
        _screen = enforce( SDL_SetVideoMode( x, y, 32, SDL_SWSURFACE ), mixin( SDL_EX ));
    }

    void closewindow()
    {
        SDL_FreeSurface( _screen );
    }

    void settext( string text, string icon )
    {
        SDL_WM_SetCaption( toStringz( text ), toStringz( icon ));
    }

    void seticon( surface src )
    {
        SDL_WM_SetIcon( src, null );
    }

    @property surface screen() { return _screen; }

    private:
        surface _screen;        

}

