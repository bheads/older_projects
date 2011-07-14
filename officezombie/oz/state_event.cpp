
#include "state_event.h"

string captions[] = {"Zombie: After eating that tuna sandwhich and some\nfriendly vomitting of blood I feel much better.\nI'm a bit hungry and sort of aggressive.\nMove me with the arrow keys to that chef\nover there so I can feast.",
"Zombie: I didn't intend on eating that chef, but bro,\nthat was amazing.",
"Office Bro: How convenient I was building a chair fort when the\nzombie Apocalypse started. That zombie can't move\nchairs. I'll just chill back here until\nthe military comes and saves me.",
"Zombie:  I'm too weak to move those chairs,\nbut maybe I can come back when I'm stronger.\nOnce I'm strong enough you can just hold space next to an object\nand I'll pull it where ever I go.\nLet's leave this room through the south door.\nI can't remember the code, maybe there's a hint on the door.",
"CEO: I realize I may have screwed you over on vacation days,\nbut if you refrain from eating my brains...\nI'll promote you.",
"Zombie: Promotions verses brains is far from a good\nbusiness proposal to a zombie.",
"Zombie: I just cleared my old workplace of all living things.\nNow it's time to work on clearing the streets and the world.\nBut that's a story for another COSC 457 project.",
"Office Bro: No. My illogical plan has failed.",
"Invalid event code"};

void StateEvent::init()
{
    playerPic.SetImage( engine.images.get( event.imagehash ));
    playerPic.SetPosition(110, 110);
    if(event.soundhash != 0)
    {
        engine.sfx.loadSound(event.soundhash, eventsnd, false);
        eventsnd.Play();
    }
}

void StateEvent::deinit()
{
    if(endgame)
        engine.pop();
}

void StateEvent::logic( F32 delta )
{
    if( engine.input.keys[ Key::Return ].pressed )
        engine.pop();
}

void StateEvent::render()
{
    engine.gfxprims.drawRect(100,100,700,500,255,255,255);
    engine.gfx.Draw( playerPic );
    engine.gfxprims.drawString(110, 300, captions[textid], 16, 0, 0, 0, 255 );
    engine.gfxprims.drawString(112, 480, "press enter to continue", 12, 0, 0, 0, 255 );
}

void StateEvent::paused()
{
}

void StateEvent::unpaused()
{
}

