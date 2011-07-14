
#include "state_puzzle.h"

void StatePuzzle::init()
{
    // setup graphics for keypad
    keypad.SetImage( engine.images.get( engine.data.puzzle.keypad_id ));
    clue.SetImage( engine.images.get( puzzle.clue_id ));

    engine.centerSprite( keypad );
    engine.centerSprite ( keypad, clue );
    clue.Move( 0, -190 );

    engine.sfx.loadSound(1350295656, correctsnd, false);
    engine.sfx.loadSound(1508172232, incorrectsnd, false);
}

void StatePuzzle::deinit()
{
}

void StatePuzzle::logic( F32 delta )
{
    if( engine.input.keys[ Key::Escape ].pressed ) {
        engine.pop();
    }

    if( firsttime ) {
        entry = "";
        firsttime = false;
    }

    if( engine.input.numeric ) {
        entry += engine.input.numericstr;
    }

    if( engine.input.keys[ Key::Back ].pressed ) {
        if( entry.size() > 0 ) {
            entry.erase( entry.size() - 1, 1 );
        }
    }

    if( engine.input.keys[ Key::Return ].pressed ) {
       if( puzzle.code == strtol( entry.c_str(), NULL, 10 )) {
           correctsnd.Play();
           puzzle.solved = 1;
           engine.pop();
       } else {
           incorrectsnd.Play();
           if( --tries <= 0 ) {

               engine.pop();
           }
       }
    }

    if( entry.empty()) {
        entry = "**********";
        firsttime = true;
    } else if( entry.size() > 10 ) {
        entry.erase( 10, entry.size() - 10 );
    }


}

void StatePuzzle::render()
{
    engine.gfx.Draw( keypad );
    engine.gfx.Draw( clue );
    engine.gfxprims.drawStringCenteredX( 245, entry, 34, 103, 143, 25 );
}

void StatePuzzle::paused()
{
}

void StatePuzzle::unpaused()
{
}

