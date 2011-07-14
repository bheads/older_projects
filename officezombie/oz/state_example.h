
/***
 * state_example
 *  Example state, copy this to make a new state
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_STATE_EXAMPLE_H
#define OZ_STATE_EXAMPLE_H

#include "engine.h"
#include "stdtype.h"
#include "error.h"
#include "state.h"

class StateEXAMPLE
    : public State
{
    public:
        StateEXAMPLE( Engine &_engine, bool blogic = true, 
            bool brender = true ) 
            : State( blogic, brender ), engine( _engine )
        {}
        ~StateEXAMPLE()
        {}

        void init();
        void deinit();
        void logic( F32 delta ); 
        void render();
        void paused();
        void unpaused();

    protected:
        Engine  &engine;
};

#endif

