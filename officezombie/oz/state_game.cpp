
#include "state_game.h"
#include "state_event.h"
#include "strfunc.h"

void StateGame::init()
{
    //set up game resources
    bar_sprite.SetImage( engine.images.get( engine.data.gameui.bar_hash ));
    bar_sprite.SetPosition( 0.0f, engine.gfx.GetHeight() - bar_sprite.GetSize().y );

    brainoutline_sprite.SetImage( engine.images.get( engine.data.gameui.brainoutline_hash ));
    brain_sprite.SetImage( engine.images.get( engine.data.gameui.brain_hash ));
    brainoutline_sprite.SetPosition( 20.0f,
            engine.gfx.GetHeight() - brainoutline_sprite.GetSize().y - 10.0f );

    menubtn_sprite.SetImage( engine.images.get( engine.data.gameui.menubtn_hash ));
    menubtn_sprite.SetPosition( engine.data.gameui.menubtn_pos.x,
            engine.data.gameui.menubtn_pos.y );

    rmap.build( engine.data.maps[ engine.data.playernode.map_id ] );

    engine.music.loadMusic( 2048533974, gamemusic, true );
    gamemusic.SetVolume(10.0f);
    gamemusic.Play();

    completed = false;
}

void StateGame::deinit()
{
    save();
    rmap.clear();
}

void StateGame::logic( F32 delta )
{


    // exit game to main menu
    if( !keyLock && engine.input.keys[ Key::Escape ].pressed ) {
        engine.pop();
    }

    if( rmap.player.moving() || keyLock ) {
        // we are in a player animation state
    } else {
        // not in a player animation state
        if( engine.input.buttons[ MOUSE_LEFT ].pressed &&
                engine.input.hoversprite( menubtn_sprite )) {
            engine.pop();
        }

    }
    rmap.update( delta );

    // test for map change
    if( rmap.map->ID() != engine.data.playernode.map_id ) {
        save();
        rmap.build( engine.data.maps[ engine.data.playernode.map_id ] );
        rmap.update( delta );
    }

    // update user stats
    // update player brain metera
    if( scale < rmap.player.scale()) {
        scale += ( delta / 4 );
        if( scale > rmap.player.scale()) {
            scale = rmap.player.scale();
        }
        if( scale >= 1.0f ) {
            // level up player!
            rmap.player.level( rmap.player.level() + 1 );
            rmap.player.exp( rmap.player.exp() - rmap.player.max_exp());
            rmap.player.max_exp( rmap.player.max_exp() * rmap.player.exp_mult());
            engine.push( new StateLevelUp( engine ));
        }
    } else if ( scale > rmap.player.scale()) {
        scale -= ( delta / 4 );
        if( scale < rmap.player.scale()) {
            scale = rmap.player.scale();
        }
    }

    brain_sprite.SetScale( scale, scale );
    engine.centerSprite( brainoutline_sprite, brain_sprite );




    // auto save
    saveTimer -= delta;
    if( saveTimer <= 0.0f && !keyLock && !rmap.player.moving() ) {
        saveTimer = engine.config.get( "Game:SaveTimer", GV_SAVE_TIMER );
        //save();
    }
}

void StateGame::render()
{
    string temp;
    U32 npccount = 0;

    // render map
 //   rmap.draw( rmap.player.x(), rmap.player.y(), 11, 13, 15, 10 );
    if((rmap.player.x() > mapcenterx + 5) || (rmap.player.x() < mapcenterx - 5))
        mapcenterx = rmap.player.x();

    if((rmap.player.y() > mapcentery + 4) || (rmap.player.y() < mapcentery - 4))
        mapcentery = rmap.player.y();

    rmap.draw( mapcenterx, mapcentery, 11, 13, 15, 10 );

    // render UI
    // engine.gfx.Draw( bar_sprite );
    engine.gfx.Draw( brain_sprite );
    engine.gfx.Draw( brainoutline_sprite );
    engine.gfx.Draw( menubtn_sprite );

    // render indicators
        //map name
    engine.gfxprims.drawString(10,10,rmap.map->name.substr(1,rmap.map->name.length()-2),20, 255, 255, 255);
        //map progress
    temp = "Humans left on map: ";
    stringAppend(temp, rmap.map->humanCount());
    engine.gfxprims.drawString(550,550,temp,20, 255, 255, 255);
        //total progress
    for(map<U32, Map>::iterator i = engine.data.maps.begin(); i != engine.data.maps.end(); i++)
        npccount += i->second.humanCount();
    temp = "Humans left in building: ";
    stringAppend(temp, npccount);
    engine.gfxprims.drawString(450,10,temp,20, 255, 255, 255);
    if((npccount == 0) && !(completed))
    {
        completed = true;
        engine.push( new StateEvent( engine, engine.data.events[2606], true ));
    }
}

void StateGame::paused()
{
}

void StateGame::unpaused()
{
}

void StateGame::save()
{
    engine.data.writetodisk( saveGameName );
}

