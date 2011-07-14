/***
 * Input
 *  Holds the games input state
 *  This will scan the event queue, gives us pressed, released and down
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#include <cstring> 

#include "input.h"

EngineInput::EngineInput()
    : closed( false ), keys(), buttons(), mouse(), alpha( false ), numeric( false ),
    text( false ), click( false ), type( false ), alphastr(), numericstr(), textstr(),
    shift( false )
{
    for( size_t i = 0; i < IO_KEY_MAX; ++i ) {
        keys[i].pressed = false;
        keys[i].released = false;
        keys[i].down = false;
        if( i < IO_MOUSE_MAX ) { 
            buttons[i].pressed = false;
            buttons[i].released = false;
            buttons[i].down = false;
        }
    }
    closed = false;
    mouse.x = 0;
    mouse.y = 0;
    mouse.w = 0;
}
    
EngineInput::~EngineInput()
{}

void EngineInput::update( Window &win )
{
    Event event;
    U32 code;
    for( size_t i = 0; i < IO_KEY_MAX; ++i ) {
        keys[i].pressed = false;
        keys[i].released = false;
        if( i < IO_MOUSE_MAX ) { 
            buttons[i].pressed = false;
            buttons[i].released = false;
        }
    }
    closed = alpha = numeric = text = click = type = false;
    alphastr.clear();
    numericstr.clear();
    textstr.clear();
    mouse.w = 0;

    while( win.GetEvent( event )) {
        if( event.Type == Event::Closed ) {
            closed = true;
        } else if( event.Type == Event::KeyPressed ) {
            code = event.Key.Code;
            shift = event.Key.Shift;
            assert( code < IO_KEY_MAX, "Key array to small: " << code );
            keys[ code ].pressed = true;
            keys[ code ].down = true;
            keys[ code ].released = false;
            if( 'a' <= code && code <= 'z' ) { 
                alpha = text = true;
                alphastr += toupper((char)code);
                textstr += toupper((char)code);
            }
            if( '0' <= code && code <= '9' ) {
                numeric = text = true;
                numericstr += (char)code;
                textstr += (char)code;
            }
            type = true;
        } else if( event.Type == Event::KeyReleased ) {
            code = event.Key.Code;
            shift = event.Key.Shift;
            assert( code < IO_KEY_MAX, "Key array to small: " << code );
            keys[ code ].pressed = false;
            keys[ code ].down = false;
            keys[ code ].released = true;
        } else if( event.Type == Event::MouseButtonPressed ) {
            code = event.MouseButton.Button;
            if( code == Mouse::Left ) code = 0;
            else if( code == Mouse::Right ) code = 1;
            else if( code == Mouse::Middle ) code = 2;
            else if( code == Mouse::XButton1 ) code = 3;
            else code = 4;
            assert( code < IO_MOUSE_MAX, "Button array is to small" );
            buttons[ code ].pressed = true;
            buttons[ code ].down = true;
            buttons[ code ].released = false;
            click = true;
        } else if( event.Type == Event::MouseButtonReleased ) {
            code = event.MouseButton.Button;
            if( code == Mouse::Left ) code = MOUSE_LEFT;
            else if( code == Mouse::Right ) code = MOUSE_RIGHT;
            else if( code == Mouse::Middle ) code = MOUSE_MIDDLE;
            else if( code == Mouse::XButton1 ) code = MOUSE_XBUTTON1;
            else code = MOUSE_ELSE;
            assert( code < IO_MOUSE_MAX, "Button array is to small" );
            buttons[ code ].pressed = false;
            buttons[ code ].down = false;
            buttons[ code ].released = true;
        } else if( event.Type == Event::MouseWheelMoved ) {
            mouse.w = event.MouseWheel.Delta;    
        } else if( event.Type == Event::MouseMoved ) {
            mouse.x = event.MouseMove.X;
            mouse.y = event.MouseMove.Y;
        }
    }
}


bool EngineInput::hoversprite( Sprite &s )
{
    F32 x, y, w, h;

    x = s.GetPosition().x;
    y = s.GetPosition().y;
    w = x + s.GetSize().x;
    h = y + s.GetSize().y;

    if( x <= mouse.x && mouse.x <= w ) {
        if( y < mouse.y && mouse.y <= h ) {
            return true;
        }
    }


    return false;
}


