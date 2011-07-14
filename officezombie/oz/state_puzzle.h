
/***
 * state_example
 *  Example state, copy this to make a new state
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_STATE_Puzzle_H
#define OZ_STATE_Puzzle_H

#include "engine.h"
#include "stdtype.h"
#include "error.h"
#include "state.h"

class StatePuzzle
    : public State
{
    public:
        StatePuzzle( Engine &_engine, PuzzleNode &_puzzle, bool blogic = true,
            bool brender = false )
            : State( blogic, brender ), engine( _engine ), puzzle( _puzzle ),
            keypad(), clue(), entry( "**********" ), firsttime( true ), tries( 3 )
        {}
        ~StatePuzzle()
        {}

        void init();
        void deinit();
        void logic( F32 delta );
        void render();
        void paused();
        void unpaused();

    protected:
        Engine      &engine;
        PuzzleNode  &puzzle;

        Sprite      keypad, clue;
        Sound       correctsnd, incorrectsnd;
        string      entry;
        bool        firsttime;
        I32         tries;
};

#endif

