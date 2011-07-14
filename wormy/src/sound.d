module src.sound;

import std.exception,
       std.conv,
       std.string;

import src.core,
       src.sdl;




class Sound
{

    int     rate = 22050;
    ushort  format = AUDIO_S16;
    int     channels = 2 ;
    int     buffers = 4096;

    this()
    {
        enforce( !(Mix_OpenAudio( rate, format, channels, buffers )), mixin(MIX_EX));        
    }   

    ~this()
    {
        Mix_HaltChannel( channel );
        Mix_CloseAudio();
    }

    void load( string song ) 
    {
        sound = enforce( Mix_LoadWAV( song ), mixin( MIX_EX ));
        
    }

    void play()
    {
        channel = Mix_PlayChannel( -1, sound, 0 );
    }

    Mix_Chunk* sound = null;
    int channel = -1;

}

