#include "splash_state.h"



void StateSplash::init()
{
    splash.SetImage( engine.images.get( engine.data.splash.background_hash ));
    walker.set( engine.data.animation[ engine.data.splash.aid ], engine.images );
    walker.position( -98.0f, 400.0f );
    walker.runloop();
    delay = engine.data.splash.delaytime;

    /*
    enforce(( bk = engine.sfx.loadSound( engine.data.splash.bk_sound, true )) != NULL,
            "Failed to load the sound stream" );
    enforce( engine.sfx.playSound( bk ) == OZ_OK,
            "Failed to play sound, sound not loaded? " );
    */
    enforce(( bk = new Music() ) != NULL, "Failed to make new music" );
    engine.music.loadMusic( engine.data.splash.bk_sound, *bk, true );
    bk->Play();

}

void StateSplash::deinit()
{
    delete bk;
    bk = NULL;
}


void StateSplash::logic( F32 delta )
{
    debug(
        engine.push( new StateProfile( engine, *bk ));
        return;
         );
    walker.update( delta );
    walker.move(( 800.0f / 6.0f ) * delta, 0 );

    // splash screen delay logic
    if( delay > 0.0f ) {
        delay -= delta;
    }
    if( delay <= 0.0f && walker.sprite.GetPosition().x > 800.0f ) {
        // launch next state!!!!
        engine.push( new StateProfile( engine, *bk ));
        delay = 0.0f;
        msg( " Launching profile screen" );
    }
}

void StateSplash::render()
{
    engine.gfx.Draw( splash );
    walker.draw( engine.gfx );
}


void StateSplash::paused()
{
}

void StateSplash::unpaused()
{
    bk->Stop();
    engine.music.dropMusic(engine.data.splash.bk_sound);
    engine.pop();
}

