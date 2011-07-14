
#ifndef OZ_GAME_DATA_H
#define OZ_GAME_DATA_H

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "error.h"
#include "stdtype.h"
#include "defaults.h"

#include "animation.h"
#include "map.h"
#include "trophies.h"
#include "movablenode.h"

// List of game data nodes
struct Pos
{
    F32 x, y;
};

struct SplashData
{
    U32 id;
    U32 background_hash;
    U32 aid;
    F32 delaytime;
    U32 bk_sound;
};

struct PuzzleData
{
    U32 id;
    U32 keypad_id;
};

struct ProfileData
{
    U32 id;
    U32 background_hash;
    U32 newdlg_hash;
    U32 exitbtn_hash, okbtn_hash, newbtn_hash;
    Pos exitbtn_pos, okbtn_pos, newbtn_pos;
    U32 fontsize;
    Pos textpos;
    U32 exists_hash;
};

struct GameUIData
{
    U32 id;
    U32 bar_hash;
    U32 brainoutline_hash, brain_hash;
    U32 menubtn_hash;
    Pos menubtn_pos;
};

struct MainMenuData
{
    U32 id;
    U32 background_hash;
    U32 resumebtn_hash, newbtn_hash, trophiesbtn_hash, settingsbtn_hash, backbtn_hash;
    Pos resumebtn_pos, newbtn_pos, trophiesbtn_pos, settingsbtn_pos, backbtn_pos;
};

struct TrophiesData
{
    U32 id;
    U32 background_hash;
};

struct MouseData
{
    U32 id;
    U32 hash;
    U32 show;
};

struct Tile
{
    U32 id;
    U32 hash;
};

struct Static
{
    U32 id;
    U32 hash;
    U32 draw_order;
};

struct PlayerNode
{
    U32             id;
    U32             exp, max_exp;
    F32             exp_mult;
    U32             level;
    U32             map_id;

    U32             green_id, red_id, level_id, level_sfx_id;

    MovableMapNode  mapnode;

};

struct PuzzleNode
{
    U32             id;

    U32             map_id;
    U32             x, y, direction;
    U32             solved;
    U32             code;
    U32             clue_id;
};

struct EventNode
{
    U32             id;
    U32             textcode;
    U32             imagehash;
    U32             soundhash;
};


class GameData
{
    public:
        GameData()
            : splash(), profile(), mainMenu(), mouse(), gameui(),
            animation(), maps(), tiles(), trophy(), static_objs(), movables(),
            puzzles()
        {}
        ~GameData()
        { }

        // load dame data from disk
        ERRCODE loadfromdisk( string );

        // write the gamedata to disk
        ERRCODE writetodisk( string );

    public:

        SplashData      splash;
        ProfileData     profile;
        MainMenuData    mainMenu;
        TrophiesData    trophies;
        MouseData       mouse;
        GameUIData      gameui;
        PlayerNode      playernode;
        PuzzleData      puzzle;

        map<U32, AnimationData> animation;
        map<U32, Map>           maps;
        map<U32, Tile>          tiles;
        map<U32, TrophyData>    trophy;
        map<U32, Static>        static_objs;
        map<U32, MovableNode>   movables;
        map<U32, PuzzleNode>    puzzles;
        map<U32, EventNode>     events;

    private:
        template <class T> void ReadBlock( FILE *, string &, T *);
        template <class T> void WriteBlock( FILE *, string &, T *);

        //void LoadAnimation( FILE *, string );

};

#endif

