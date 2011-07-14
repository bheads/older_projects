
/***
 * state_example
 *  Example state, copy this to make a new state
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_STATE_MAINMENU_H
#define OZ_STATE_MAINMENU_H

#include "engine.h"
#include "stdtype.h"
#include "error.h"
#include "state.h"

class StateMainMenu
    : public State
{
    public:
        StateMainMenu( Engine &_engine, Music &bks , string saveGame, bool blogic = true,
            bool brender = true )
            : State( blogic, brender ), engine( _engine ), bksnd( bks ), saveGameName( saveGame )
        {}
        ~StateMainMenu()
        {}

        void init();
        void deinit();
        void logic( F32 delta );
        void render();
        void paused();
        void unpaused();

    protected:
        Engine  &engine;

        Music &bksnd;

        string saveGameName;

        Sprite bgImg, resumebtn, newbtn, trophiesbtn, settingsbtn, backbtn;
};

#endif

