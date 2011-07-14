module src.worm;


import src.core;

enum uint DIR_N = 0;
enum uint DIR_E = 1;
enum uint DIR_S = 2;
enum uint DIR_W = 3;

static const ushort width = 10, height = 10, offset = 6;
static const wormlength = 1;

struct Node
{
    short x, y;
}

class Worm
{

    this( Core core )
    {
        this.core = core;
        gen.seed( SDL_GetTicks());
    }

    void spawn( uint corner ) 
    {
        switch ( corner ) {
            case DIR_N:
                dir = DIR_S;
                _head.x = 0; _head.y = 0;
                color = 0x00ff0000;
                colorhead = 0xffff0000;
                break;
            case DIR_E:
                dir = DIR_S;
                _head.x = 49; _head.y = 0;
                color = 0x0000ff00;
                colorhead = 0xff00ff00;
                break;
            case DIR_S:
                dir = DIR_N;
                _head.x = 49; _head.y = 49;
                color = 0x0000ff00;
                colorhead = 0xff00ff00;
                break;
            case DIR_W:
            default:
                dir = DIR_N;
                _head.x = 0; _head.y = 49;
                color = 0x0000ff00;
                colorhead = 0xff00ff00;
                break;
        }
        _body.length = wormlength;
        foreach( ref node; _body ) {
            node.x = _head.x;
            node.y = _head.y;
        }
    }

    void draw()
    {
        foreach( node; _body ) {
            core.gfx.box( core.screen, cast(short)(( node.x * width ) + offset + 1), 
                    cast(short)(( node.y * height ) + offset + 1 ), width-2, height-2, color );
        }
        core.gfx.box( core.screen, cast(short)(( _head.x * width ) + offset + 1), 
                cast(short)(( _head.y * height ) + offset + 1 ), width-2, height-2, colorhead );
    }

    void ai( Worm[] worms ) 
    {
        bool skiptest = false;
        uint tries = 6;

        if( uniform( 0.0f, 1.0f ) >= 0.95f ) {
            skiptest = true;
        }

        if( !skiptest && !crashtest( worms )) {
            return;
        }

        while( tries ) {
            --tries;
            dir = uniform( 0, 4, gen );
            if( !crashtest( worms )) return;
        }
        
        dir = 0;
        if( !crashtest( worms )) return;
        dir = 1;
        if( !crashtest( worms )) return;
        dir = 2;
        if( !crashtest( worms )) return;
        dir = 3;
        if( !crashtest( worms )) return;

    }



    bool crashtest( Worm[] worms )
    {
        Node tmp = _head;
        switch( dir ) {
            case DIR_N:
                tmp.y--;
                break;
            case DIR_E:
                tmp.x++;
                break;
            case DIR_S:
                tmp.y++;
                break;
            case DIR_W:
                tmp.x--;
                break;
        }

        if( tmp.x < 0 || tmp.y < 0 || tmp.x >= 50 || tmp.y >= 50 ) {
            return true;
        }

        foreach( worm; worms ) {
            if( tmp == worm._head ) return true;
            foreach( node; worm._body ) {
                if( tmp == node ) return true;
            }

        }

        return false;
    }

    void update( Worm[] worms )
    {
        foreach_reverse( i, ref node; _body ) {
            if( i == 0 ) break;
            node.x = _body[i-1].x;
            node.y = _body[i-1].y;
        }
        _body[0].x = _head.x;
        _body[0].y = _head.y;
        ++age;

        if( age >= ( _body.length * 1.25 )) {
            age = 0;
            _body ~= _body[$-1];
        }
        
        // dont move if you cant! 
        if( crashtest( worms )) { 
            if( _body.length > 1 ) {
                _body.length = _body.length - 1;
            }
            return;
        }

        switch( dir ) {
            case DIR_N:
                _head.y--;
                break;
            case DIR_E:
                _head.x++;
                break;
            case DIR_S:
                _head.y++;
                break;
            case DIR_W:
                _head.x--;
                break;
        }

        if( _head.x < 0 ) _head.x = 0;
        if( _head.y < 0 ) _head.y = 0;
        if( _head.x >= 50 ) _head.x = 49;
        if( _head.y >= 50 ) _head.y = 49;
            
    }


    Core    core;
    static  Random gen;
    int     dir = DIR_S;
    Node    _head;
    Node[]  _body;
    uint    color;
    uint    colorhead;
    uint    age;


}

