/***
 * engine
 *  Core of the game, the game engine
 *  contains all of the working parts
 *  that make up the game
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_ENGINE_H
#define OZ_ENGINE_H

#include <string>
#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "stdtype.h"
#include "error.h"
#include "inireader.h"
#include "defaults.h"
#include "input.h"
#include "images.h"
#include "sfx.h"
#include "state.h"
#include "gamedata.h"
#include "gfx.h" //Rending Graphics Primitives

// resource mamanger stuff
#include "pack.h"

typedef vector< State* > StateStack;

class Engine
{
    public:
        Engine();
        ~Engine();

        ERRCODE start( const string & );
        ERRCODE stop();

        bool isrunning();
        void getinput();
        F32  getdelta();
        U32  fps();

        void clear( U8 r = 0, U8 g = 0, U8 b = 0 );
        void display();

        void push( State *state );
        void pop();
        bool hasstates();
        void runstates( F32 );
        void updatestates();

        // this should get moved to GFX, center b to a
        void centerSprite( Sprite &a, Sprite &b );
        // Center a to the screen
        void centerSprite( Sprite &a  );

        Config          config;
        EngineInput     input;
        RenderWindow    gfx;
        PackManager     packman;
        ImageManager    images;
        GameData        data;
        SFX             sfx;
        SFXMusic        music;
	GFX		gfxprims;

    private:
        float           fps_time;
        U32             fps_count, fps_val;
        String          fps_text;
        bool            fps_draw;

        StateStack      states;
        U32             pops;
        StateStack      pushes;

        Sprite          mouse_sprite;
};

#endif

