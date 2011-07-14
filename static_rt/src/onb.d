module src.onb;

import src.vector;

struct ONB
{
    enum ONB_EPSILON = 0.01f;

    this( ref const(ONB) o )
    {
        set( o );
    }

    this( vector a, vector b, vector c )
    {
        set( a, b, c );
    }

    void set( ref const(ONB) o )
    {
        u = o.u;
        v = o.v;
        w = o.w;
    }

    void set( vector a, vector b, vector c )
    {
        u = a;
        v = b;
        w = c;
    }

    void initFromU( vector _u )
    {
        auto n = vector( 1.0f, 0.0f, 0.0f );
        auto m = vector( 0.0f, 1.0f, 0.0f );
        u = _u.normal();
        v = u.cross( n );
        if( v.length < ONB_EPSILON ) {
            v = u.cross( m );
        }
        w = u.cross( v );
    }

    void initFromV( vector _v )
    {
        auto n = vector( 1.0f, 0.0f, 0.0f );
        auto m = vector( 0.0f, 1.0f, 0.0f );
        v = _v.normal;
        u = v.cross( n );
        if( u.length2 < ONB_EPSILON ) {
            u = v.cross( m );
        }
        w = u.cross( v );
    }

    void initFromW( vector _w )
    {
        auto n = vector( 1.0f, 0.0f, 0.0f );
        auto m = vector( 0.0f, 1.0f, 0.0f );
        w = _w.normal;
        u = w.cross( n );
        if( v.length < ONB_EPSILON ) {
            u = w.cross( m );
        }
        v = w.cross( v );
    }

    void initFromUV( vector _u, vector _v )
    {
        u = _u.normal;
        w = cross( _u, _v ).normal;
        v = w.cross( u );
    }

    void initFromVU( vector _v, vector _u )
    {
        v = _v.normal;
        w = _u.cross( _v ).normal;
        u = v.cross( w );
    }

    void initFromUW( vector _u, vector _w )
    {
        u = _u.normal;
        v = _w.cross( _u ).normal;
        w = u.cross( v );
    }

    void initFromWU( vector _w, vector _u )
    {
        w = _w.normal;
        v = _w.cross( _u ).normal;
        w = v.cross( w );
    }

    void initFromVW( vector _v, vector _w )
    {
        v = _v.normal;
        u = _v.cross( _w ).normal;
        w = u.cross( v );
    }

    void initFromWV( vector _w, vector _v )
    {
        w = _w.normal;
        u = _v.cross( _w ).normal;
        v = w.cross( u );
    }

    vector u, v, w;
}
