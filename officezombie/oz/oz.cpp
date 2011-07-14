/***
 *  Office Zombie
 *      a puzzle adventure with brainz
 *
 *  oz.cpp
 *      program main function, will spawn the engine
 *      and init the state stack
 *
 *  Byron Heads bheads@emich.edu
 *
 *
 *
 ***/

#include <iostream>
using namespace std;

#include "stdtype.h"
#include "error.h"
#include "engine.h"

#include "splash_state.h"

void oz();

int main( I32 argc, char **argv )
{

    oz();
    return( 0 );
}

void oz()
{
    msg( "Running in debug mode" );
    Engine engine;
    ERRCODE ecode;

    enforce( engine.start( "oz.ini" ) == OZ_OK, 
            "Failed to start game engine" );

    engine.push( new StateSplash( engine ));
    engine.updatestates();

    msg( "Entering game loop " << engine.isrunning() << engine.hasstates());

    while( engine.isrunning() && engine.hasstates()) {
        engine.getinput();
        if( engine.input.closed ) {
            engine.stop();
            continue;
        }

        engine.clear();
        engine.runstates( engine.getdelta());
        engine.display();
    }

    msg( "Exiting game loop" );
    enforce( engine.stop() == OZ_OK, "Failed to stop game engine" );
}

