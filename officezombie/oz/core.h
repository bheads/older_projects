

#ifndef OZ_CORE_H
#define OZ_CORE_H



#include "engine.h"
#include "inireader.h"
#include "input.h"



class Core
{
    public:

        Core()
            : config(), input(), gfx(), packman(), images( packman ), data(), 
            sfx( packman, 100.0f ), music( packman, 100.0f )
        {}
        ~Core()
        {}

        Engine          engine
        Config          config;
        EngineInput     input;
        PackManager     packman;
        ImageManager    images;
        GameData        data;
        SFX             sfx;
        SFXMusic        music;

}



#endif

