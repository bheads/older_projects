module  src.gameworld;

import  std.stdio,
         std.conv,
         std.string;

import  src.gameobjects;

class GameWorld
    : StaticObject
{

    this( short _x, short _y, short width, short height, int _id )
    {
        super( _x, _y, width, height, _id );
    }
      
    void clear()
    {
        st.length = 0;
        dy.length = 0;    
    }


    // BAD BAD BAD!!! I am just assumming
    // D will throw exceptions when we hit a bad file!
    void load( GameObjects go, string fn )
    {
        auto fin = File( fn, "r" );
        string      buf;
        string[]    items;
        
        fin.readln( buf );
        items = buf.split();
       // debug writeln( buf, " ", items );
        _w = parse!short( items[0] );
        _h = parse!short( items[1] );
        nx = parse!short( items[2] );
        ny = parse!short( items[3] );
        
        while( fin.readln( buf )) {
            items = buf.strip.split;
            debug writeln( buf, " ", items );
            if( items[0] == "s" ) {
                int tmp = parse!int( items[5]);
                st ~= new StaticObject( parse!short( items[1] ), parse!short(items[2] ),
                    parse!short( items[3] ), parse!short( items[4] ), tmp);
                go.gm.load( tmp, items[6] );            
            } else if( items[0] == "e" ) {
                int tmp = parse!int( items[5]);
                ev ~= new EventObject( parse!short( items[1] ), parse!short(items[2] ),
                    parse!short( items[3] ), parse!short( items[4] ), tmp, 
                    go.hf[ parse!int(items[6]) ] );
                go.gm.load( tmp, items[7] );         
            } else if( items[0] == "i" ) {
                go.gm.load( parse!int( items[1]), items[2] );
            } else if( items[0] == "a" ) {
                int tmp = parse!int( items[5]);
                debug writeln( items[5], " = ", tmp );
                ai ~= new AIObject( parse!short( items[1] ), parse!short(items[2] ),
                    parse!short( items[3] ), parse!short( items[4] ), tmp, 
                    go.ahf[ parse!int(items[6]) ], go.auf[ parse!int(items[7])] );
                go.gm.load( tmp, items[8] );  
                ai[$-1].setbounds( 0, 0, w, h );   
            }
            
        }
    
    }

    StaticObject[]  st;
    DynamicObject[] dy;
    EventObject[]   ev;
    AIObject[]      ai;
    short nx, ny;



}

