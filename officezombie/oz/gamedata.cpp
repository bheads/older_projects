
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#include "gamedata.h"
#include "defaults.h"


ERRCODE GameData::loadfromdisk( string filename )
{
    U32 id = 0, rr = 0;
    FILE *fp;

    debug( cout << "Reading game data from: " << filename << endl );

    // open file to read from
    enforce(( fp = fopen( filename.c_str(), "rb" )) != NULL,
            "Failed to open " << filename << " for reading ( " <<
            strerror( errno ) << " )" << endl );

    // Read Item ID then call the function
    while((rr = fread( &id, 1, sizeof( U32 ), fp )) > 0 ) {
        cout << "ID: " << id << endl;
        enforce( rr == sizeof( U32 ),
                "Failed to read from " << filename << ": "
                << strerror( errno ));
         // move back to reread is
         fseek( fp, -sizeof( U32 ), SEEK_CUR );
         if( id == GD_SPLASH_ID ) {
            debug( cout << "Found A Splash Menu" << endl );
            ReadBlock( fp, filename, &splash );
         } else if( id == GD_PROFILE_ID ) {
            debug( cout << "Found A Profile Menu" << endl );
            ReadBlock( fp, filename, &profile );
         } else if( id == GD_PUZZLE_ID ) {
            debug( cout << "Found A Puzzle Menu" << endl );
            ReadBlock( fp, filename, &puzzle );
         } else if( id == GD_MAINMENU_ID ) {
            debug( cout << "Found A Main Menu" << endl );
            ReadBlock( fp, filename, &mainMenu );
         } else if( id == GD_TROPHIES_ID ) {
            debug( cout << "Found A Trophies Menu" << endl );
            ReadBlock( fp, filename, &trophies );
         } else if( id == GD_MOUSE_ID ) {
            debug( cout << "Found A Mouse Config" << endl );
            ReadBlock( fp, filename, &mouse );
         } else if( id == GD_GAME_UI_ID ) {
            debug( cout << "Found A Game UI" << endl );
            ReadBlock( fp, filename, &gameui );
         } else if( id == GD_PLAYER_ID ) {
            debug( cout << "Found A Player Node" << endl );
            ReadBlock( fp, filename, &playernode );
         } else if( GD_TILE_ID_MIN <= id && id <= GD_TILE_ID_MAX ) {
            debug( cout << "Found A tile" << endl );
            ReadBlock( fp, filename,  &(tiles[id]));
         } else if( GD_ANIM_ID_MIN <= id && id <= GD_ANIM_ID_MAX ) {
            debug( cout << "Found A animation" << endl );
            animation[id].read( fp, filename );
         } else if( GD_MAP_ID_MIN <= id && id <= GD_MAP_ID_MAX ) {
            debug( cout << "Found A map" << endl );
            maps[id].read( fp, filename );
         } else if( GD_TROPHY_ID_MIN <= id && id <= GD_TROPHY_ID_MAX ) {
            debug( cout << "Found A trophy" << endl );
            trophy[id].read( fp, filename );
         } else if( GD_STATIC_ID_MIN <= id && id <= GD_STATIC_ID_MAX ) {
            debug( cout << "Found A static obj" << endl );
            ReadBlock( fp, filename,  &(static_objs[id]));
         } else if( GD_MOVABLE_ID_MIN <= id && id <= GD_MOVABLE_ID_MAX ) {
            debug( cout << "Found A movable" << endl );
            ReadBlock( fp, filename, &(movables[id]));
         } else if( GD_PUZZLE_ID_MIN <= id && id <= GD_PUZZLE_ID_MAX ) {
            debug( cout << "Found A puzzle" << endl );
            ReadBlock( fp, filename, &(puzzles[id]));
         } else if( GD_EVENT_ID_MIN <= id && id <= GD_EVENT_ID_MAX ) {
            debug( cout << "Found A puzzle" << endl );
            ReadBlock( fp, filename, &(events[id]));
         } else {
                enforce( false, "Invalid Mod Node ID " << id << " in " <<
                        filename );
        }
    }

    debug( cout << "Done!" << endl );
    // close file
    fclose( fp );
    return( OZ_OK );
}


ERRCODE GameData::writetodisk( string filename )
{
    FILE *fp = NULL;
    AnimationNode anode;
    U32 utmp;

    debug( cout << "Writing game data to: " << filename << endl );
    // open file to write too
    enforce(( fp = fopen( filename.c_str(), "wb" )) != NULL,
            "Failed to open " << filename << " for writting ( " <<
            strerror( errno ) << " )" << endl );

    // write the splash data
    debug( cout << "Writting splash data" << endl );
    WriteBlock( fp, filename, &splash );
    debug( cout << "Writting profile data" << endl );
    WriteBlock( fp, filename, &profile );
    debug( cout << "Writting puzzle data" << endl );
    WriteBlock( fp, filename, &puzzle );
    debug( cout << "Writting main menu data" << endl );
    WriteBlock( fp, filename, &mainMenu );
    debug( cout << "Writting tropies data" << endl );
    WriteBlock( fp, filename, &trophies );
    debug( cout << "Writting mouse data" << endl );
    WriteBlock( fp, filename, &mouse );
    debug( cout << "Writting game ui data" << endl );
    WriteBlock( fp, filename, &gameui );
    debug( cout << "Writting player data" << endl );
    WriteBlock( fp, filename, &playernode );

    // write statics
    debug( cout << "Writting static list" << endl );
    for( map<U32, Static>::iterator i = static_objs.begin();
            i != static_objs.end(); ++i ) {
        WriteBlock( fp, filename, &(i->second));
    }

    // write movables
    debug( cout << "Writting movables list" << endl );
    for( map<U32, MovableNode>::iterator i = movables.begin();
            i != movables.end(); ++i ) {
        WriteBlock( fp, filename, &(i->second));
    }

    // write tiles
    debug( cout << "Writting tile list" << endl );
    for( map<U32, Tile>::iterator i = tiles.begin(); i != tiles.end(); ++i ) {
        WriteBlock( fp, filename, &(i->second));
    }

    // write animation data
    debug( cout << "Writting animation list" << endl );
    for( map<U32, AnimationData>::iterator i = animation.begin();
            i != animation.end(); ++i ) {
        (*i).second.write( fp, filename );
    }

    // write maps
    debug( cout << "Writting map list" << endl );
    for( map<U32, Map>::iterator i = maps.begin(); i != maps.end(); ++i ) {
        (*i).second.write( fp, filename );
    }

    // write puzzles
    debug( cout << "Writting puzzle list" << endl );
    for( map<U32, PuzzleNode>::iterator i = puzzles.begin(); i != puzzles.end(); ++i ) {
        WriteBlock( fp, filename, &(i->second));
    }

    // write puzzles
    debug( cout << "Writting event list" << endl );
    for( map<U32, EventNode>::iterator i = events.begin(); i != events.end(); ++i ) {
        WriteBlock( fp, filename, &(i->second));
    }

    // write trophies
    debug( cout << "Writting trophies list" << endl );
    for( map<U32, TrophyData>::iterator i = trophy.begin();
            i != trophy.end(); ++i ) {
        (*i).second.write( fp, filename );
    }


    // close file
    enforce( fclose( fp ) == 0, "Failed to close file " << filename << " ( " <<
            strerror( errno ) << " )" << endl );

    debug( cout << "Done." << endl );

    return( OZ_OK );
}

template <class T>
void GameData::ReadBlock( FILE *fp, string &filename, T *block )
{
    enforce( fread( block, 1, sizeof( T ), fp ) == sizeof( T ),
            "Failed to read from " << filename << " (" << strerror( errno ) << ")" );
}

template <class T>
void GameData::WriteBlock( FILE *fp, string &filename, T *block )
{
    enforce( fwrite( block, 1, sizeof( T ), fp ) == sizeof( T ),
            "Failed to write to " << filename << " (" << strerror( errno ) << ")" );
}

