
#ifndef SFX_H
#define SFX_H

#include <map>
using namespace std;

#include <SFML/Audio.hpp>
using namespace sf;

#include "stdtype.h"
#include "error.h"
#include "pack.h"

class FileInfo
{
    public:
    ERRCODE loadInfo(U8*, U32);
    U8* data;
    U32 size;
    bool dropped;
};

class SFX
{
    public:
        SFX( PackManager &p,  F32 vol = 50.0f );
        virtual ~SFX();
        SoundBuffer &loadSound( U32, Sound &, bool = true );

        ERRCODE setVolume(F32 newVol);
        F32 getVolume();

    protected:
    private:
        F32 masterVolume;
        PackManager &packman;
        map<U32, SoundBuffer> sounds;
};


class SFXMusic
{
    public:
        SFXMusic( PackManager &p,  F32 vol = 50.0f );
        virtual ~SFXMusic();
        ERRCODE loadMusic( U32, Music &, bool = true );
        ERRCODE dropMusic(U32);

        ERRCODE setVolume(F32 newVol);
        F32 getVolume();

    protected:
    private:
        F32 masterVolume;
        PackManager &packman;
        map<U32, FileInfo> musics;
};

#endif // SFX_H
