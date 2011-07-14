/***
 * Input
 *  Holds the games input state
 *  This will scan the event queue, gives us pressed, released and down
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/


#ifndef OZ_INPUT_H
#define OZ_INPUT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "stdtype.h"
#include "error.h"
#include "defaults.h"

struct KeyType
{
    bool    pressed;
    bool    down;
    bool    released;
};

struct Position
{
    I32 x, y, w;
};

class EngineInput
{
    public:
        EngineInput();
        ~EngineInput();

        void update( Window & );
        bool hoversprite( Sprite & );

        bool        closed;
        KeyType     keys[ IO_KEY_MAX ];        
        KeyType     buttons[ IO_MOUSE_MAX ];        
        Position    mouse;

        bool        alpha, numeric, text, click, type;
        string      alphastr, numericstr, textstr;
        bool        shift;
};

#endif

