
/***
 * state_Profile
 *  Profile state, copy this to make a new state
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_STATE_PROFILE_H
#define OZ_STATE_PROFILE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

#include "engine.h"
#include "stdtype.h"
#include "error.h"
#include "state.h"
#include "filefunc.h"

class StateProfile
    : public State
{
    public:
        StateProfile( Engine &_engine, Music & bks, bool blogic = true,
            bool brender = true )
            : State( blogic, brender ), engine( _engine ),
            bksnd( bks ), bkimg(), exitbtn(), okbtn(), newbtn(), newdlg(),
            exists(), profilestr(), newstring(),
            state( 0 ), dirs(), selected( 0 ), scroll_top( 0 )
        {}
        ~StateProfile()
        {
            dirs.clear();
        }

        void init();
        void deinit();
        void logic( F32 delta );
        void render();
        void paused();
        void unpaused();

    private:
        void findprofiles();

    protected:
        Engine  &engine;
        Music   &bksnd;
        Sprite  bkimg, exitbtn, okbtn, newbtn;
        Sprite  newdlg, exists;
        String  profilestr;
        string  newstring;

        U32     state;
        vector<string> dirs;
        IDX     selected, scroll_top;
};

#endif

