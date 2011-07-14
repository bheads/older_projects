
/***
 * state_example
 *  Example state, copy this to make a new state
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_STATE_GAME_H
#define OZ_STATE_GAME_H

#include <string>
#include <map>
#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

#include "engine.h"
#include "stdtype.h"
#include "error.h"
#include "state.h"
#include "rendermap.h"

#include "state_levelup.h"

class StateGame
    : public State
{
    public:
        StateGame( Engine &_engine, string saveGame, bool blogic = true,
            bool brender = true )
            : State( blogic, brender ), engine( _engine ), saveGameName( saveGame ),
            saveTimer( engine.config.get( "Game:SaveTimer", GV_SAVE_TIMER, true )),
            keyLock( false ), bar_sprite(), brain_sprite(), brainoutline_sprite(),
            menubtn_sprite(), rmap( _engine ),
            px( 0 ), py( 0 ), mapcenterx( 5 ), mapcentery( 5 ), scale( 0.001f )
        {}
        ~StateGame()
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

        U32     saveTimer;
        bool    keyLock;

        Sprite  bar_sprite, brain_sprite, brainoutline_sprite, menubtn_sprite;

        RenderMap   rmap;

    private:
        void save();
        I32 px, py;
        U32 mapcenterx, mapcentery;
        F32 scale;
        bool completed;

        Music gamemusic;
};

#endif

