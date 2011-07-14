module test; 

import  derelict.sdl.sdl; 
version( all ) { 
    pragma( lib, "DerelictSDL" ); 
    pragma( lib, "DerelictUtil" ); 
    pragma( lib, "dl" ); 
} 

void main() 
{ 
    DerelictSDL.load(); 
    SDL_Init( SDL_INIT_EVERYTHING ); 
    
    SDL_Surface* screen = SDL_SetVideoMode( 800, 600, 32, SDL_SWSURFACE ); 
    SDL_Event event; 


    while( true ) { 
        if( SDL_PollEvent( &event )) { 
            if( event.type == SDL_QUIT ) break; 
        }    

        SDL_FillRect( SDL_GetVideoSurface(), null, 0x00000000 ); 

        SDL_UpdateRect( SDL_GetVideoSurface(), 0, 0, 0, 0); 
    }    

    SDL_Quit(); 
    DerelictSDL.unload(); 
} 
