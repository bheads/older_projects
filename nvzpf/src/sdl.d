module  src.sdl;

version( Windows ) {
	pragma( lib, "DerelictSDL" );
	pragma( lib, "DerelictSDLimage" );
    pragma( lib, "DerelictSDLttf" );
	pragma( lib, "DerelictUtil" );
}


import  std.stdio,
        std.exception,
        std.conv;

public
import  derelict.sdl.sdl,
        derelict.sdl.image,
        derelict.sdl.ttf;

public enum SDL_EX = "new Exception( \"<\" ~ to!string(__LINE__ ) ~ \">\""
                     " ~ to!string( SDL_GetError()))";
public enum IMG_EX = "new Exception( to!string( IMG_GetError()))";
public enum TTF_EX = "new Exception( to!string( TTF_GetError()))";
enum IMG_INIT_ALL = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

alias SDL_Surface* surface;
alias SDL_Rect rect;

static this()
{
    debug writeln( "Loading SDL Dynamic Libs" );
    DerelictSDL.load();
    DerelictSDLImage.load();
    DerelictSDLttf.load();
    debug writeln ("Done" );

    debug writeln( "Initlizing SDL" );
    enforce( !SDL_Init( SDL_INIT_EVERYTHING ), mixin( SDL_EX ));
    enforce( IMG_Init( IMG_INIT_ALL ) == IMG_INIT_ALL, mixin( IMG_EX ));
    enforce( !TTF_Init(), mixin( TTF_EX ));
    debug writeln( "Done" );
}

static ~this()
{
    debug writeln( "Doing SDL Quits" );
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    debug writeln( "Done" );

    debug writeln( "Unloading SDL Dynamic Libs" );
    DerelictSDLttf.unload();
    DerelictSDLImage.unload();
    DerelictSDL.unload();
    debug writeln( "Done" );
}





