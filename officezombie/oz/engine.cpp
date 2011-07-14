

#include <sstream>

#include "engine.h"

Engine::Engine()
    : config(), input(), gfx(), packman(), images( packman ), data(), sfx( packman, 100.0 ), gfxprims(gfx, packman),
    music( packman, 50.0 ),
    fps_time( 0.0f ), fps_count( 0 ), fps_val( 0 ), fps_text(),
    fps_draw(false ), states(), pops( 0 ), pushes(), mouse_sprite()
{}

Engine::~Engine()
{
    states.clear();
    pushes.clear();
}

ERRCODE Engine::start( const string &configfile )
{
    ERRCODE ecode;

    try {
        msg( "Loading config file: " << configfile );
        enforce(( ecode = config.load( configfile, true )) == OZ_OK,
                "Failed to load config file: " << configfile << " -> "
                << GetError( ecode ));

        string pack = config.get( "Engine:MainPack", PACK_MAIN, true );
        msg( "Loading Packmanager: " << pack );
        packman.load( pack );

        string gamedata = config.get( "Engine:GameData", GAME_DATA, true );
        msg( "Loading Gamedata: " << gamedata );
        //data.writetodisk( gamedata );
        data.loadfromdisk( gamedata );

        msg( "Creating game window: " );
        VideoMode vm(
            config.get( "Engine:Width", GFX_WIDTH, true ),
            config.get( "Engine:Height", GFX_HEIGHT, true ),
            config.get( "Engine:BPP", GFX_BPP, true ));
        if( !vm.IsValid()) {
            cout << "Invalid video mode in config file.  Valid Modes Are: " << endl;
            U32 vmcount = VideoMode::GetModesCount();
            for ( U32 i = 0; i < vmcount; ++i) {
                VideoMode mode = VideoMode::GetMode(i);
                cout << i + 1 << ": " << mode.Width << "x" << mode.Height << " " <<
                    mode.BitsPerPixel << "bpp" << endl;
            }

            return( OZ_ENGINE_FAILED_TO_START );
        }

        U32 winstyle =
            ( config.getbool( "Engine:Titlebar", GFX_TITLEBAR, true ) ?
                Style::Titlebar : 0 )
            | ( config.getbool( "Engine:Resize", GFX_RESIZE, true ) ?
                Style::Resize : 0 )
            | ( config.getbool( "Engine:CloseButton", GFX_CLOSEBUTTON,
                true ) ? Style::Close : 0 )
            | ( config.getbool( "Engine:Fullscreen", GFX_FULLSCREEN,
                true ) ? Style::Fullscreen : 0 );
        gfx.Create( vm, config.get( "Engine:Title", GFX_TITLE, true ),
                winstyle );
        gfx.SetPosition(( VideoMode::GetDesktopMode().Width / 2 ) - ( vm.Width / 2 ),
                ( VideoMode::GetDesktopMode().Height / 2 ) - ( vm.Height / 2 ));
        gfx.UseVerticalSync( config.getbool( "Engine:VerticalSync",
                    GFX_VERTICALSYNC, true ));
        gfx.SetFramerateLimit( config.get( "Engine:FrameLimit",
                    GFX_FRAMELIMIT, true ));
        gfx.SetCursorPosition( vm.Width / 2, vm.Height / 2 );
        gfx.EnableKeyRepeat( config.getbool( "Engine:KeyRepeat",
                    GFX_KEYREPEAT, true ));
        gfx.ShowMouseCursor( config.getbool( "Engine:ShowOSCursor",
                    GFX_SHOWCURSOR, true ));
        fps_draw = config.getbool( "Engine:ShowFPS", GFX_DRAWFPS, true );

        fps_text.SetFont(sf::Font::GetDefaultFont());
        fps_text.SetPosition( 0.0f, 0.0f );
        fps_text.SetSize( 14 );
        fps_text.SetColor( Color( 255, 255, 255));
        fps_text.SetText( "FPS: 0" );

        // setup mouse
        mouse_sprite.SetImage( images.get( data.mouse.hash ));

        //test for must
        if( config.get( "Game:Mute", GV_MUTED, true )) {
            music.setVolume( 0.0f );
            sfx.setVolume( 0.0f );
        }

        // set font
        gfxprims.setFont( 135538232 );


    } catch( const char *e ) {
        return( OZ_ENGINE_FAILED_TO_START );
    }

    return( OZ_OK );
}


ERRCODE Engine::stop()
{
    ERRCODE ecode;

    try {

        msg( "Closing window" );
        gfx.Close();

        msg( "Saving config file: " << config.configfilename());
        enforce(( ecode = config.save()) == OZ_OK,
                "Failed to save config file: " << config.configfilename() <<
                " -> " << GetError( ecode ));
    } catch( const char *e ) {
        return( OZ_ENGINE_FAILED_TO_STOP );
    }

    return( OZ_OK );
}


bool Engine::isrunning()
{
    return( gfx.IsOpened());
}

void Engine::getinput()
{
    input.update( gfx );
}

F32 Engine::getdelta()
{
    return( gfx.GetFrameTime());
}

U32 Engine::fps()
{
    return( fps_val );
}

void Engine::clear( U8 r, U8 g, U8 b )
{
    // count frames
    stringstream ss;
    ++fps_count;
    fps_time += getdelta();
    if( fps_time >= 1.0f ) {
        fps_val = fps_count;
        fps_count = 0;
        fps_time = 0.0f;
        ss << "FPS: " << fps_val;
        fps_text.SetText( ss.str());
    }

    mouse_sprite.SetPosition( input.mouse.x, input.mouse.y );

    // clear should only be called once
    gfx.Clear( Color( r, g, b ));
}

void Engine::display()
{
    if( fps_draw ) {
        gfx.Draw( fps_text );
    }
    if( data.mouse.show ) {
        gfx.Draw( mouse_sprite );
    }
    gfx.Display();
}



void Engine::push( State *state )
{
    enforce( state != NULL, "Pushed a NULL state" );
    /*
       // push states in real time, may cause bugs
    if( states.size() > 0 ) {
        // pause top state
        states.back()->paused();
    }
    // init the state
    state->init();
    states.push_back( state );
    */
    // push states to a temp list, then push when its safe to push
    pushes.push_back( state );
}

void Engine::pop()
{
    ++pops;
}

bool Engine::hasstates()
{
    return( states.size() > 0 );
}

void Engine::runstates( F32 delta )
{
    size_t len = states.size(), i;
    // run logic
    for( i = len - 1; i >= 0; --i ) {
        /*
           // bottom down logic update loop
        if( states[i]->blocklogic() || i == 0 ) {
            for(; i < len; ++i ) {
                states[i]->logic( delta );
            }
            break;
        }
        */
        // switch logic to top down, makes more sense
        states[i]->logic( delta );
        if( states[i]->blocklogic()) break;
    }

    // run render
    for( i = len - 1; i >= 0; --i ) {
        if( states[i]->blockrender() || i == 0 ) {
            for(; i < len; ++i ) {
                states[i]->render();
            }
            break;
        }
    }
    updatestates();
}

void Engine::updatestates()
{
    // run pushes
    for( size_t i = 0; i < pushes.size(); ++i ) {
        if( states.size() > 0 ) states.back()->paused();
        pushes[i]->init();
        states.push_back( pushes[i] );
    }
    pushes.clear();

    // Runs pops
    while( pops > 0 ) {
        enforce( states.size() > 0, "Poping an empty state stack" );
        states.back()->deinit();
        delete( states.back());
        states.pop_back();
        if( states.size() > 0 ) {
            states.back()->unpaused();
        }
        --pops;
    }
}


void Engine::centerSprite( Sprite &a, Sprite &b )
{
    F32 x = a.GetPosition().x, y = a.GetPosition().y;
    F32 w = a.GetSize().x * a.GetScale().x, h = a.GetSize().y * a.GetScale().y;
    F32 cx = x + ( w / 2.0f ), cy = y + ( h / 2.0f );
    w = b.GetSize().x;
    h = b.GetSize().y;
    b.SetPosition( cx - ( w / 2.0f ), cy - ( h / 2.0f ));
}

void Engine::centerSprite( Sprite &a  )
{
    F32 cx = gfx.GetWidth() / 2.0f, cy = gfx.GetHeight() / 2.0f;
    F32 w = a.GetSize().x, h = a.GetSize().y;
    a.SetPosition( cx - ( w / 2.0f ), cy - ( h / 2.0f ));
}

