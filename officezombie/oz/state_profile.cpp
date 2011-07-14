
#include "state_profile.h"
#include "state_mainMenu.h"

void StateProfile::init()
{
    bkimg.SetImage( engine.images.get( engine.data.profile.background_hash ));
    newdlg.SetImage( engine.images.get( engine.data.profile.newdlg_hash ));
    exists.SetImage( engine.images.get( engine.data.profile.exists_hash ));

    exists.SetPosition(( bkimg.GetSize().x - exists.GetSize().x)/2.0f,
            ( bkimg.GetSize().y - exists.GetSize().y )/2.0f);
    newdlg.SetPosition(( bkimg.GetSize().x - newdlg.GetSize().x)/2.0f,
            ( bkimg.GetSize().y - newdlg.GetSize().y )/2.0f);

    exitbtn.SetImage( engine.images.get( engine.data.profile.exitbtn_hash ));
    okbtn.SetImage( engine.images.get( engine.data.profile.okbtn_hash ));
    newbtn.SetImage( engine.images.get( engine.data.profile.newbtn_hash ));

    exitbtn.SetPosition( engine.data.profile.exitbtn_pos.x, engine.data.profile.exitbtn_pos.y );
    okbtn.SetPosition( engine.data.profile.okbtn_pos.x, engine.data.profile.okbtn_pos.y );
    newbtn.SetPosition( engine.data.profile.newbtn_pos.x, engine.data.profile.newbtn_pos.y );

    profilestr.SetFont( Font::GetDefaultFont());
    profilestr.SetSize( engine.data.profile.fontsize );
    profilestr.SetColor( Color( 0, 0, 0 ));
    profilestr.SetText( "" );
    profilestr.SetPosition( engine.data.profile.textpos.x, engine.data.profile.textpos.y );

    engine.data.mouse.show = 1;
    MakeDir( engine.config.get( "Game:ProfilesPath", PROFILE_PATH, true ));
    findprofiles();
}

void StateProfile::deinit()
{
}

void StateProfile::logic( F32 delta )
{
    string path;
    bool found;

    switch( state ) {
        case 0:
            if( engine.input.keys[ Key::Escape ].pressed ) {
                engine.pop();
            }

            // test mouse clicks
            if( engine.input.buttons[ MOUSE_LEFT ].pressed ) {
                if( engine.input.hoversprite( exitbtn )) {
                    engine.pop();
                }
                if( engine.input.hoversprite( okbtn ) && dirs.size() > 0 ) {
                    path = engine.config.get( "Game:ProfilesPath", PROFILE_PATH, true );
                    if( path[ path.size() - 1 ] != '/' ) path += '/';
                    path += dirs[selected] + "/save.mod";
                    debug( cout << "Loading " << dirs[selected] << " profile: " << path << endl );
                    //loading disabled
                    if( !engine.config.getbool( "Game:DisableLoading", true, true )) {
			    engine.data.loadfromdisk( path );
                    }
                    engine.push( new StateMainMenu( engine, bksnd, path ));
                }
                if( engine.input.hoversprite( newbtn )) {
                    newstring.clear();
                    profilestr.SetText( "" );
                    state = 1;
                }


            }
            // test key presses
            if( engine.input.keys[ Key::Up ].pressed ) {
                if( selected > 0 ) {
                    if( --selected < scroll_top ) --scroll_top;
                }
            } else if( engine.input.keys[ Key::Down ].pressed ) {
                if( selected < ( dirs.size() - 1 )) {
                    if( ++selected > ( scroll_top + 13 )) ++scroll_top;
                }
            } else if( engine.input.keys[ Key::Return ].pressed ) {
                if( dirs.size() > selected ) {
                    path = engine.config.get( "Game:ProfilesPath", PROFILE_PATH, true );
                    if( path[ path.size() - 1 ] != '/' ) path += '/';
                    path += dirs[selected] + "/save.mod";
                    debug( cout << "Loading " << dirs[selected] << " profile: " << path << endl );
                    //loading disabled
                    if( !engine.config.getbool( "Game:DisableLoading", true, true )) {
			    engine.data.loadfromdisk( path );
                    }
                    engine.push( new StateMainMenu( engine, bksnd, path ));
                }
            }
            break;
        case 1:
            if( engine.input.keys[ Key::Escape ].pressed ) {
                state = 0;
            }

            if( engine.input.keys[ Key::Back ].pressed ||
                    engine.input.keys[ Key::Delete ].pressed ) {
                newstring = newstring.substr( 0, newstring.size() - 1 );
                profilestr.SetText( newstring.c_str());
            }

            if( engine.input.text ) {
                newstring += engine.input.textstr;
                newstring = newstring.substr( 0, 32 );
                profilestr.SetText( newstring.c_str());
            }

            if( engine.input.keys[ Key::Return ].pressed ) {
                if( newstring.size() > 0 ) {
                    state = 2;
                }
            }
            break;
        case 2:
            path = engine.config.get( "Game:ProfilesPath", PROFILE_PATH, true );
            found = false;
            for( size_t i = 0; i < dirs.size(); ++i ) {
                cout << newstring << " == " << dirs[i] << endl;
                if( newstring.compare( dirs[i] ) == 0 ) {
                    state = 3;
                    found = true;
                    engine.input.click = engine.input.type = false;
                    break;
                }
            }

            if( !found ) {
                if( path[ path.size() -1 ] != '/' ) path += '/';
                path += newstring;
                if( path[ path.size() -1 ] != '/' ) path += '/';
                // make profile
                MakeDir( path );
                path += "save.mod";
                engine.data.writetodisk( path );
                state = 0;
            }
            findprofiles();
            break;
        case 3:
            if( engine.input.click || engine.input.type ) state = 0;
            break;
    }

}

void StateProfile::render()
{
    engine.gfx.Draw( bkimg );

    engine.gfx.Draw( exitbtn );
    engine.gfx.Draw( newbtn );
    if( dirs.size() > 0 ) engine.gfx.Draw( okbtn );

    for( IDX i = 0; i < dirs.size() && i < 14; ++i ) {
        if( scroll_top + i == selected ) {
            engine.gfxprims.drawString( 30, 150 + ( i * 30 ), dirs[ scroll_top + i], 22,
                    255, 255, 255 );
        } else {
            engine.gfxprims.drawString( 30, 150 + ( i * 30 ), dirs[ scroll_top + i], 22,
                    145, 145, 145 );
        }
    }

    if( state == 1 ) {
        engine.gfx.Draw( newdlg );
        engine.gfx.Draw( profilestr );
    }

    if( state == 3 ) {
        engine.gfx.Draw( exists );
    }
}

void StateProfile::paused()
{
}

void StateProfile::unpaused()
{
    // reload original game data set
    string gamedata = engine.config.get( "Engine:GameData", GAME_DATA );
    engine.data.loadfromdisk( gamedata );
    engine.data.mouse.show = 1;
    findprofiles();
}

void StateProfile::findprofiles()
{
    string path = engine.config.get( "Game:ProfilesPath", PROFILE_PATH, true );

    dirs.clear();
    GetDirList( dirs, path );
}


