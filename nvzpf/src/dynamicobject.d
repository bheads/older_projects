module  src.dynamicobject;

import     std.exception,
            std.conv,
            std.math;

import  src.gameobjects;


class DynamicObject
    : StaticObject
{
    this( short _x, short _y, short width, short height, int _id )
    {
        super( _x, _y, width, height, _id );
        _fid = _id;
    }

    void update( float delta = 0.0, float ax = 0.0, float ay = 0.0 )
    {   
        _fx = cast(short)(px + ( _vx * delta ) + ( 0.5 * ax * ( delta ^^ 2 )));
        _fy = cast(short)(py + ( _vy * delta ) + ( 0.5 * ay * ( delta ^^ 2 )));
        _vx = ( _vx + ax ) * 0.97;
        _vy = ( _vy + ay ) * 0.97;
    
        // close to zero test        
        if( 0.001 > _vx && _vx > -0.001 ) _vx = 0.0;
        if( 0.001 > _vy && _vy > -0.001 ) _vy = 0.0;

        // bound test 
        if( _fx < _minx ) _fx = _minx;
        if( _fy < _miny ) _fy = _miny;
        if( _fx > _maxx ) _fx = _maxx;
        if( _fy > _maxy ) _fy = _maxy;
       
    }

    void setbounds( short _minx, short _miny, short _maxx, short _maxy )
    {
        this._minx = _minx; this._miny = _miny; 
        this._maxx = _maxx; this._maxy = _maxy;
    }

    @property float vx() { return _vx; }
    @property float vy() { return _vy; }
       
    void accept()
    {
        px = _fx; py = _fy; _id = _fid;
    }
    
    void reject( float delta )
    {
        _vx = 0.0; _vy = 0.0;
        //update( delta );
    }
    
     bool pixeltest( GameObjects go, Camera cam, StaticObject obj )
     {
        uint a, b, c = 0xff00ff;
        surface sa = go.gm( _fid ), sb = go.gm( obj.id );
               
        int left = ( _fx >= obj.x ? _fx : obj.x ) - _fx;
        int top = ( _fy >= obj.y ? _fy : obj.y ) - _fy;
        int right = (( _fx + w ) <= ( obj.x + obj.w ) ? _fx + w : obj.x + obj.w ) - _fx;
        int bottom = (( _fy + h ) <= ( obj.y + obj.h ) ? _fy + h : obj.y + obj.h ) - _fy;
        
        enforce( !SDL_LockSurface( sa ), mixin( SDL_EX ));
        scope(exit) SDL_UnlockSurface( sa );
        enforce( !SDL_LockSurface( sb ), mixin( SDL_EX ));
        scope(exit) SDL_UnlockSurface( sb );
        
        int ox, oy;
        foreach( ty; top..bottom ) {
            foreach( tx; left..right ) {
                 ox = ( _fx + tx ) - obj.x; 
                 oy = ( _fy + ty ) - obj.y;
                
                 a = (cast(uint*)sa.pixels)[ ty * w + tx ];
                 if( a == c ) continue;
                
                 b = (cast(uint*)sb.pixels)[ oy * obj.w + ox ];
                 if( b == c ) continue;
                 
                 debug {
                     go.gfx.clear( go.screen, &rect(cast(short)( obj.x+ox - 4 - cam.x),
                        cast(short)( obj.y+oy - 4 - cam.y), 5, 5), 0xff00); 
                     go.gfx.clear( go.screen, &rect(cast(short)( x+tx - 3 - cam.x),
                        cast(short)( y+ty - 3 - cam.y), 3, 3), 0xff0000); 
                 }
              
              
                 return true;
            }
        }      
        return false;
    }
   
        int     nodamage = 0;
        int     _fid;
        int     _life = 3;
    protected:
        short   _fx, _fy;
        float  _vx = 0.0, _vy = 0.0;
        short   _minx = 0, _miny = 0, _maxx = 2048, _maxy = 768;


}
    
