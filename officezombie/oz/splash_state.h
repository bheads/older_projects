
/***
 * splash_state
 *  Main Splash screen state
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_STATE_SPLASH_H
#define OZ_STATE_SPLASH_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

#include "stdtype.h"
#include "error.h"
#include "state.h"
#include "engine.h"
#include "animation.h"

#include "state_profile.h"

class StateSplash
    : public State
{
    public:
        StateSplash( Engine &_engine, bool blogic = true,
            bool brender = true )
            : State( blogic, brender ), engine( _engine ), splash(),
            delay( 0.0f ), walker(), bk( NULL )
        {}
        ~StateSplash()
        {}

        void init();
        void deinit();
        void logic( F32 delta );
        void render();
        void paused();
        void unpaused();

    protected:
        Engine      &engine;
        Sprite      splash;
        F32         delay;
        Animation   walker;
        Music       *bk;
};

#endif

