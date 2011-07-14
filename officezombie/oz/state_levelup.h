#ifndef OZ_STATE_LEVELUP_H
#define OZ_STATE_LEVELUP_H

#include "engine.h"
#include "stdtype.h"
#include "error.h"
#include "state.h"

class StateLevelUp
    : public State
{
    public:
        StateLevelUp( Engine &_engine, bool blogic = false,
            bool brender = false )
            : State( blogic, brender ), engine( _engine ), popupImg(), 
            timeAlive( 3.0f ), scale( 0.5f ), grow( true ), popupSnd()
        {}
        ~StateLevelUp()
        {}

        void init();
        void deinit();
        void logic( F32 delta );
        void render();
        void paused();
        void unpaused();

    protected:
        Engine  &engine;
        Sprite  popupImg;

        F32     timeAlive, scale;
        bool    grow;

        Sound   popupSnd;
};

#endif

