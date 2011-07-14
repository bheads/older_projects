
/***
 * state_example
 *  Example state, copy this to make a new state
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_STATE_EVENT_H
#define OZ_STATE_EVENT_H

#include "engine.h"
#include "stdtype.h"
#include "error.h"
#include "state.h"

class StateEvent
    : public State
{
    public:
        StateEvent( Engine &_engine, EventNode &_event, bool isendgame = false, bool blogic = true,
            bool brender = false )
            : State( blogic, brender ), engine( _engine ), event( _event ),
            playerPic(), eventsnd(), textid( _event.textcode ), endgame( isendgame )
        {}
        ~StateEvent()
        {
            //eventsnd.ResetBuffer();
        }

        void init();
        void deinit();
        void logic( F32 delta );
        void render();
        void paused();
        void unpaused();

    protected:
        Engine      &engine;
        EventNode   &event;

        Sprite      playerPic;
        Sound       eventsnd;
        U32         textid;
        bool        endgame;
};

#endif

