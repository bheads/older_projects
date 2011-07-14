
/***
 * state_trophies
 *  Trophie state,
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_STATE_TROPHIES_H
#define OZ_STATE_TROPHIES_H

#include "engine.h"
#include "stdtype.h"
#include "error.h"
#include "state.h"

class StateTrophies
    : public State
{
    public:
        StateTrophies( Engine &_engine, string saveGame, bool blogic = true,
            bool brender = true )
            : State( blogic, brender ), engine( _engine ), saveGameName( saveGame )
        {}
        ~StateTrophies()
        {}

        void init();
        void deinit();
        void logic( F32 delta );
        void render();
        void paused();
        void unpaused();

    protected:
        Engine  &engine;

        string  saveGameName;

        Sprite  bgImg;
        Sprite  trophy451;
};

#endif

