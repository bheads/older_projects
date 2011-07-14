
#include "animation.h"



void AnimationData::clear()
{
    id = frametime = 0;
    frames.clear();
}

void AnimationData::read( FILE *fp, string &filename )
{
    U32 frame_hash = 0;
    AnimationNode anode;

    ReadBlock( fp, filename, &anode );
    id = anode.id;
    frametime = anode.frametime;
    for( U32 i = 0; i < anode.framecount; ++i ) {
        ReadBlock( fp, filename, &frame_hash );
        frames.push_back( frame_hash );
    }
}

void AnimationData::write( FILE *fp, string &filename )
{
    U32 frame_hash = 0;
    AnimationNode anode;
    
    anode.id = id;
    anode.frametime = frametime;
    anode.framecount = frames.size();
    WriteBlock( fp, filename, &anode );
    for( size_t i = 0; i < anode.framecount; ++i ) {
        frame_hash = frames[i];
        WriteBlock( fp, filename, &frame_hash );
    }
}


void Animation::update( F32 delta )
{
    if( isrunning()) {
        framecounter += delta;
        if( framecounter >= frametime ) {
            framecounter = 0.0f;
            if( ++frameindex >= frames.size() ) {
                frameindex = 0;
                if( !loop ) stop();
            }
            sprite.SetImage( *frames[ frameindex ] );
        }
    }
}

void Animation::draw( RenderWindow &gfx )
{
    gfx.Draw( sprite );
}

void Animation::set( AnimationData &ad, ImageManager &images )
{
    if( id != ad.ID()) {
        frametime = ad.frametime;
        id = ad.ID();
        frames.clear();
        for( size_t i = 0; i < ad.frames.size(); ++i ) {
            frames.push_back( &images.get( ad.frames[i] ));
        }
        reset();
    }
}

