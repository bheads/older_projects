module  src.ninja;

import  std.math;

import  src.gameobjects;

class Ninja
    : DynamicObject
{
    int     dir;

    this( short _x, short _y, short width, short height, int _id )
    {
        super( _x, _y, width, height, _id );
        _id = ID_NINJA_DOWN;
        _life = ID_HUD_HEARTS.length;
    }
   
    void set( short nx, short ny )
    {
        px = nx; py = ny;    
    }
    
    override void update( float delta = 0.0, float ax = 0.0, float ay = 0.0 )
    {
        super.update( delta, ax, ay );
        if( abs( vx ) > abs( vy )) {
            if( vx > 0.0 ) {
                _fid = ID_NINJA_RIGHT;
            } else if( vx < 0.0 ) {
                _fid = ID_NINJA_LEFT;
            }
        } else {
            if( vy > 0.0 ) {
                _fid = ID_NINJA_DOWN;
            } else if( vy < 0.0 ) {
                _fid = ID_NINJA_UP;
            }
        }  
    }
    
    @property bool hasstars() { return _hasstars; }
    @property void hasstars( bool v ) { _hasstars = v; }
    
    @property int stars() { return _stars; }
    @property int star() { return --_stars; }
    
    @property int money() { return _money; }
    @property void money( int a ) { _money += a; }
    
    //private:
        bool    _hasstars;
        int     _stars = ID_NINJA_STARS.length;
        
        int     _money;
        
        

}


