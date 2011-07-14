module src.vector;

import std.math;

public alias vector color;

struct vector
{
    this( ref const (vector) v )
    {
        cell[] = v.cell[];
    }

    this( float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f )
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    this( float[4] _cell ) 
    { 
        cell[] = _cell[]; 
    }

    void set( float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f )
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    void set( float[4] _cell )
    {
        cell[] = _cell[];
    }

    ref vector opUnary(string op)()
        if( op == "+" || op == "-" )
    {
        mixin( "cell[] = " ~ op ~ "cell[];" );
        return(this);
    }


    vector opBinary(string op)( vector v )
        if( op == "+" || op == "-" || op == "*" || op == "/" )
    {
        return vector( mixin( "x " ~ op ~ " v.x" ),
                mixin( "y " ~ op ~ " v.y" ),
                mixin( "z " ~ op ~ " v.z" ),
                mixin( "w " ~ op ~ " v.w" ));
    }

    vector opBinary(string op)( float k )
        if( op == "*" || op == "/" || op == "+" || op == "-" )
    {
        return vector( mixin( "x " ~ op ~ " k" ),
                mixin( "y " ~ op ~ " k" ),
                mixin( "z " ~ op ~ " k" ),
                mixin( "w " ~ op ~ " k" ));
    }

    vector opBinaryRight(string op)( float k )
        if( op == "*" || op == "/" || op == "+" || op == "-" )
    {
        return vector( mixin( "k " ~ op ~ " x" ),
                mixin( "k " ~ op ~ " y" ),
                mixin( "k " ~ op ~ " z" ),
                mixin( "k " ~ op ~ " w" ));
    }


    ref vector opOpAssign(string op)( float k )
        if( op == "" || op == "*" || op == "/" || op == "+" || op == "-" )
    {
        mixin( "cell[] " ~ op ~ "= k;" );
        return( this );
    }

    ref vector opOpAssign(string op)( vector v )
        if( op == "+" || op == "-" || op == "" || op == "*" || op == "/" )
    {
        mixin( "cell[] " ~ op ~ "= v.cell[];" );
        return( this );
    }

    ref vector opOpAssign(string op)( float[4] _cell )
        if( op == "+" || op == "-" || op == "" || op == "*" || op == "/" )
    {
        mixin( "cell[] " ~ op ~ "= _cell[];" );
        return( this );
    }

    float length()
    {
        return( sqrt( x * x + y * y + z * z ));
    }

    float length2()
    {
        return( x * x + y * y + z * z );
    }

    float dot( vector v )
    {
        return( x * v.x + y * v.y + z * v.z );
    }

    vector cross( vector v )
    {
        return vector( y * v.z - z * v.y,
                z * v.x - x * v .z, x * v.y - y * v.y );
    }

    vector normal() const
    {
        return vector( this ).normalize;
    }

    vector normal()
    {
        return vector( this ).normalize;
    }

    ref vector normalize()
    {
        float len = length;
        cell[] /= len;
        return this;
    }

    const bool opEquals( ref const(vector) v )
    {
        if( this is v ) return true;
        return( approxEqual( x, v.x ) && approxEqual( y, v.y ) &&
                approxEqual( z, v.z ) && approxEqual( w, v.w ) ? true : false );
    }

    void clamp( float min = 0.0f, float max = 1.0f )
    {
        x = ( x < min ? min : x > max ? max : x );
        y = ( y < min ? min : y > max ? max : y );
        z = ( z < min ? min : z > max ? max : z );
        w = ( w < min ? min : w > max ? max : w );
    }

    vector clamped( float min = 0.0f, float max = 1.0f )
    in
    {
        assert( min < max );
    }
    out( v )
    {
        assert( min <= v.x && v.x <= max );
        assert( min <= v.y && v.y <= max );
        assert( min <= v.z && v.z <= max );
        assert( min <= v.w && v.w <= max );
    }
    body
    {
        return vector( ( x < min ? min : x > max ? max : x ),
                ( y < min ? min : y > max ? max : y ),
                ( z < min ? min : z > max ? max : z ),
                ( w < min ? min : w > max ? max : w ));
    }

    ubyte R() { return cast(ubyte)(r*255); }
    ubyte G() { return cast(ubyte)(g*255); }
    ubyte B() { return cast(ubyte)(b*255); }
    ubyte A() { return cast(ubyte)(a*255); }

    union
    {
        struct{ float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f; }
        struct{ float r, g, b, a; }
        struct{ float[4] cell; }
    }
}


float dot( vector a, vector b )
{
    return( a.x * b.x + a.y * b.y + a.z * b.z );
}

vector cross( vector a, vector b )
{
    auto ret = vector( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, 
            a.x * b.y - a.y * b.y );
    return ret;
}

vector normal( vector v )
{
    return vector( v ).normal;
}

float tripleProduct( vector v1, vector v2, 
        vector v3 )
{
    return( dot( cross( v1, v2 ), v3 ));
}

float distance( vector a, vector b )
{
    return ( a - b ).length;
}

