
#include "state_mainMenu.h"
#include "state_trophies.h"
#include "state_game.h"
#include "gfx.h"

void StateMainMenu::init()
{
    bgImg.SetImage( engine.images.get( engine.data.mainMenu.background_hash ));
    resumebtn.SetImage( engine.images.get( engine.data.mainMenu.resumebtn_hash ));
    newbtn.SetImage( engine.images.get( engine.data.mainMenu.newbtn_hash ));
    trophiesbtn.SetImage( engine.images.get( engine.data.mainMenu.trophiesbtn_hash ));
    settingsbtn.SetImage( engine.images.get( engine.data.mainMenu.settingsbtn_hash ));
    backbtn.SetImage( engine.images.get( engine.data.mainMenu.backbtn_hash ));

    resumebtn.SetPosition( engine.data.mainMenu.resumebtn_pos.x, engine.data.mainMenu.resumebtn_pos.y );
    newbtn.SetPosition( engine.data.mainMenu.newbtn_pos.x, engine.data.mainMenu.newbtn_pos.y );
    trophiesbtn.SetPosition( engine.data.mainMenu.trophiesbtn_pos.x, engine.data.mainMenu.trophiesbtn_pos.y );
    settingsbtn.SetPosition( engine.data.mainMenu.settingsbtn_pos.x, engine.data.mainMenu.settingsbtn_pos.y );
    backbtn.SetPosition( engine.data.mainMenu.backbtn_pos.x, engine.data.mainMenu.backbtn_pos.y );
    engine.data.mouse.show = 1;

}

void StateMainMenu::deinit()
{
    engine.data.writetodisk(saveGameName);
}

void StateMainMenu::logic( F32 delta )
{
    if( engine.input.keys[ Key::Escape ].pressed ) {
        engine.pop();
    }

    // test mouse clicks
    if( engine.input.buttons[ MOUSE_LEFT ].pressed ) {
        if( engine.input.hoversprite( resumebtn )) {
            engine.push( new StateGame( engine, saveGameName ));
        }
        if( engine.input.hoversprite( newbtn )) {
            string gamedata = engine.config.get( "Engine:GameData", GAME_DATA );
            engine.data.loadfromdisk( gamedata );
            engine.data.writetodisk(saveGameName);
            engine.push( new StateGame( engine, saveGameName ));
        }
/*        if( engine.input.hoversprite( trophiesbtn )) {
            engine.push( new StateTrophies( engine, saveGameName ));
        }
        if( engine.input.hoversprite( settingsbtn )) {
            engine.pop();
        }*/
        if( engine.input.hoversprite( backbtn )) {
            engine.pop();
        }
    }

    //test key presses
    if(engine.input.keys[ Key::Return ].pressed)
        engine.push( new StateGame( engine, saveGameName ));
}

void StateMainMenu::render()
{
    engine.gfx.Draw( bgImg );

    engine.gfxprims.drawString(10,10,saveGameName.substr(9,saveGameName.length() - 18),25);

    engine.gfx.Draw( resumebtn );
    engine.gfx.Draw( newbtn );
 //   engine.gfx.Draw( trophiesbtn );
 //   engine.gfx.Draw( settingsbtn );
    engine.gfx.Draw( backbtn );
}

void StateMainMenu::paused()
{
    bksnd.Pause();
    engine.data.mouse.show = 0;
}

void StateMainMenu::unpaused()
{
    engine.data.mouse.show = 1;
    engine.data.writetodisk(saveGameName);
    bksnd.Play();
}
