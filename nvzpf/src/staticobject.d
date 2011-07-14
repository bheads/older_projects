module  src.staticobject;

import     std.exception,
            std.conv;

import  src.gameobjects;


class StaticObject
{
    
    this( short _x, short _y, short width, short height, int _id )
    {
        px = _x; py = _y;
        _w = width; _h = height;
        this._id = _id;
        _alive = true;
    } 

    bool boxtest( StaticObject obj )
    {
        if( obj.x <= px + w && obj.x + obj.w >= px )    {
            if( obj.y <= py + h && obj.y + obj.h >= py ) {               
                return true;
            }
        }
        return false;
    }
    
    void cbox( GameObjects go, Camera cam, StaticObject obj )
    {
        // find top left
        uint left = ( x > obj.x ? x : obj.x ) - cam.x;
        uint top = ( y > obj.y ? y : obj.y ) - cam.y;
        uint right = (( x + w ) < ( obj.x + obj.w ) ? x + w : obj.x + obj.w ) - cam.x;
        uint bottom = (( y + h ) < ( obj.y + obj.h ) ? y + h : obj.y + obj.h ) - cam.y;
        
        with( go ) {
            gfx.line( screen, left, top, right, top, 0xff0000 );
            gfx.line( screen, left, top, left, bottom, 0xff0000 );
            gfx.line( screen, right, top, right, bottom, 0xff0000 );
            gfx.line( screen, left, bottom, right, bottom, 0xff0000 );
        }
    }

    uint size() { return w * h; }

    @property short x() { return px; }
    @property short y() { return py; }
    @property short w() { return _w; }
    @property short h() { return _h; }
    @property int id() { return _id; }
    @property bool alive() { return _alive; }
    @property void alive( bool v) { _alive = v; }
    
    @property void id( int i) { _id += 1; }
    
    protected:
        bool    _alive;
        short   px, py;
        short   _w, _h;
        int     _id;
}



