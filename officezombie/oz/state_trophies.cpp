
#include "state_trophies.h"

void StateTrophies::init()
{
    bgImg.SetImage( engine.images.get( engine.data.trophies.background_hash ));

    trophy451.SetImage( engine.images.get( engine.data.trophy[451].imageHash ));
    trophy451.SetColor(Color(255,255,255,128));

    trophy451.SetPosition(10,10);
}

void StateTrophies::deinit()
{
}

void StateTrophies::logic( F32 delta )
{
    if( engine.input.keys[ Key::Escape ].pressed ) {
        engine.pop();
    }
}

void StateTrophies::render()
{
    engine.gfx.Draw( bgImg );
    engine.gfx.Draw( trophy451 );
}

void StateTrophies::paused()
{
}

void StateTrophies::unpaused()
{
}
