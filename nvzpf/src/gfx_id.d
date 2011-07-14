module  src.gfx_id;

import  std.conv;

enum  int ID_ICON = 0x00;
enum  string FN_ICON = "gfx/icon.png";

enum  int ID_MENU_NEW = 0x01;
enum  int ID_MENU_NEW_ARROW = 0x02;
enum  int ID_MENU_QUIT = 0x03;
enum  int ID_MENU_QUIT_ARROW = 0x04;
enum  int ID_MENU_PAUSE = 0x05;
enum  int ID_MENU_STARS = 0x06;
enum  int ID_MENU_DEAD = 0x07;
enum  int ID_MENU_EXIT = 0x08;
enum  int ID_MENU_MAIN = 0x09;


enum  string FN_MENU_NEW = "gfx/menu/new.png";
enum  string FN_MENU_NEW_ARROW = "gfx/menu/newarrow.png";
enum  string FN_MENU_QUIT = "gfx/menu/quit.png";
enum  string FN_MENU_QUIT_ARROW = "gfx/menu/quitarrow.png";
enum  string FN_MENU_PAUSE = "gfx/menu/pause.png";
enum  string FN_MENU_STARS = "gfx/menu/stars.png";
enum  string FN_MENU_DEAD = "gfx/menu/dead.png";
enum  string FN_MENU_EXIT = "gfx/menu/exit.png";
enum  string FN_MENU_MAIN = "gfx/menu/main.png";

enum  int ID_NINJA_UP = 0x10;
enum  int ID_NINJA_DOWN = 0x11;
enum  int ID_NINJA_LEFT = 0x12;
enum  int ID_NINJA_RIGHT = 0x13;

enum  string FN_NINJA_UP = "gfx/ninja/up.png";
enum  string FN_NINJA_DOWN = "gfx/ninja/down.png";
enum  string FN_NINJA_LEFT = "gfx/ninja/left.png";
enum  string FN_NINJA_RIGHT = "gfx/ninja/right.png";

enum int ID_NINJA_STARS[] = repint( 0x2000, 20 );
enum string FN_NINJA_STARS[] = repstr( "gfx/stars/", 0, 20, ".png" );


enum int ID_HUD_LIFE = 0x20;
enum string FN_HUD_LIFE = "gfx/ninja/life.png";

enum int ID_HUD_HEARTS[] = [ 0x21, 0x22, 0x23, 0x24, 0x25 ];
enum string FN_HUD_HEARTS[] = [ "gfx/ninja/heart0.png", "gfx/ninja/heart1.png",
                                 "gfx/ninja/heart2.png", "gfx/ninja/heart3.png",
                                 "gfx/ninja/heart4.png" ];

int[] repint( int start, int count )
{
    int[] ret;
    foreach( i; start .. start+count )
        ret ~= i;
    return ret;
}

string [] repstr( string pre, int start, int count, string post )
{
    string[] ret;
    foreach( i; start..start+count )
        ret ~= pre ~ to!string( i ) ~ post;
    return ret;         
}
