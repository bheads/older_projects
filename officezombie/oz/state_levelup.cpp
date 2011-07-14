
#include "state_levelup.h"

void StateLevelUp::init()
{
    popupImg.SetImage( engine.images.get( engine.data.playernode.level_id ));
    engine.sfx.loadSound( engine.data.playernode.level_sfx_id, popupSnd, false );
    popupSnd.Play();
}

void StateLevelUp::deinit()
{
}

void StateLevelUp::logic( F32 delta )
{
    timeAlive -= delta;
    if( timeAlive <= 0.0f ) {
        engine.pop();
    } else {
        if( grow ) {
            scale += 4.0f * delta;
            if( scale >= 1.5f ) {
                grow = false;
            }
        } else {
            scale -= 4.0f * delta;
            if( scale <= 0.5f ) {
                grow = true;
            }

        }
    }
    popupImg.SetScale( scale, scale );
    engine.centerSprite( popupImg );
}

void StateLevelUp::render()
{
    engine.gfx.Draw( popupImg );
}

void StateLevelUp::paused()
{
}

void StateLevelUp::unpaused()
{
}

