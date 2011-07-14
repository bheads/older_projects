#include "sfx.h"

ERRCODE FileInfo::loadInfo(U8* dataPtr, U32 length)
{
    data = dataPtr;
    size = length;
    dropped = false;

    return OZ_OK;
}



SFX::SFX( PackManager &p,  F32 vol)
    : masterVolume( vol ), packman( p ), sounds()
{ }

SFX::~SFX()
{
    sounds.clear();
}

SoundBuffer &SFX::loadSound( U32 hash, Sound &sound, bool loop )
{
    U32 size;
    U8 *data;
    if( sounds.find( hash ) == sounds.end()) {
        data = packman.getNEWdata( hash, size );
        sounds[hash].LoadFromMemory( (char *)data, size );
        delete[] data;
    }
    sound.SetBuffer( sounds[hash] );
    sound.SetVolume( masterVolume );
    sound.SetLoop( loop );
    return(sounds[hash]);
}

ERRCODE SFX::setVolume(F32 newVol)
{
    if(newVol < 0.0f || newVol > 100.0f )
        return OZ_SFX_INVALID_VOLUME_VALUE;

    masterVolume = newVol;
    return OZ_OK;
}

F32 SFX::getVolume()
{
    return masterVolume;
}



SFXMusic::SFXMusic( PackManager &p,  F32 vol)
    : masterVolume( vol ), packman( p ), musics()
{ }

SFXMusic::~SFXMusic()
{
    for( map<U32, FileInfo>::iterator i = musics.begin();
            i != musics.end(); ++i ) {
        if( !i->second.dropped ) {
            delete[] i->second.data;
            i->second.data = NULL;
        }
    }
}

ERRCODE SFXMusic::loadMusic( U32 hash, Music &music, bool loop )
{
    U32 size = 0;
    U8 *data = 0;
    FileInfo musicInfo;

    if( musics.find( hash ) == musics.end()) {
        data = packman.getNEWdata( hash, size );
        musicInfo.loadInfo(data, size);
        musics[hash] = musicInfo;
    }
    else if(musics[hash].dropped) {
        data = packman.getNEWdata( hash, size );
        musicInfo.loadInfo(data, size);
        musics[hash] = musicInfo;
    }

    if(!music.OpenFromMemory( (char *)musics[hash].data, musics[hash].size ))
    {
        return OZ_SFX_FILENOTFOUND_ERROR;
    }

    music.SetVolume( masterVolume );
    music.SetLoop( loop );
    return OZ_OK;
}

ERRCODE SFXMusic::dropMusic(U32 hash)
{
    musics[hash].dropped = true;
    delete[] musics[hash].data;
    musics[hash].data = NULL;
    musics.erase( hash );

    return OZ_OK;
}

ERRCODE SFXMusic::setVolume(F32 newVol)
{
    if(newVol < 0.0f || newVol > 100.0f )
        return OZ_SFX_INVALID_VOLUME_VALUE;

    masterVolume = newVol;
    return OZ_OK;
}

F32 SFXMusic::getVolume()
{
    return masterVolume;
}
