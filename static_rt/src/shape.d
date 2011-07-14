module src.shape;

import std.math, std.stdio;

import src.vector, src.ray;

struct hitdat
{
    this( float _t, color _c ) { t = _t; c = _c; }

    float t = float.max;
    color c;
}

interface Shape
{
    float intersect( ray r, float tmax );
    vector normal( vector at );

    bool islight();

    float diffuse();
    float specular();
    float reflection();

    color Color();
}

class Plane2: Shape
{
    this( vector p, vector n, color _color, float d, float r )
    {
        this.p = p;
        this.n = n.normal;
        this._color = _color;
        this.d = d;
        this.r = r;
    }

    vector normal( vector at ) { return n; }
    bool islight() { return false; }
    float diffuse() { return d; }
    float specular() { return 1.0f - d; }
    float reflection() { return r; }
    color Color() { return _color; }

    float intersect( ray r, float tmax )
    {
        float dnom = dot( r.d, n );
        // need to make sure we are very accurate
        if( fabs( dnom ) < 0.000000000000000001f ) return -1.0f;
        float t = -(dot( r.o - p, n )/ dnom);
        if( 0.0f <= t && t <= tmax ) return t;
        return -1.0f;
    }

    vector p, n;
    color _color;
    float d, r;
}

class Triangle : Shape
{
    this( vector a, vector b, vector c, color _color, float diffuse, float reflection )
    {
        this.a = a;
        this.b = b;
        this.c = c;
        this._color = _color;
        l_diffuse = diffuse;
        l_reflection = reflection;
        N = cross( b - a, c - a );
        dist = dot( N, a );
        ab = b - a;
        ac = c - a;
    }

    vector normal( vector at ) { return N; }
    bool islight() { return false; }
    float diffuse() { return l_diffuse; }
    float specular() { return 1.0f - l_diffuse; }
    float reflection() { return l_reflection; }
    color Color() { return _color; }

    float intersect( ray r, float tmax )
    {
        vector p = r.o;
        vector q = r.at( tmax );
        vector qp = p - q;

        float d = dot( qp, N );
        if( d <= 0.0f ) return -1.0f;

        vector ap = p - a;
        float t = dot( ap, N );
        if( t < 0.0f || d < t ) return -1.0f;

        vector e = cross( qp, ap );
        float v = dot( ac, e );
        if( v < 0.0f || d < v ) return -1.0f;
        float w = -dot( ab, e );
        if( w < 0.0f || d < v + w ) return -1.0f;

        return qp.length * (t / d);

    }

    vector a, b, c, N, ab, ac;
    color _color;
    float l_diffuse, l_reflection, dist;
}


class Plane : Shape
{
    this( vector n, float d, color c, float diff, float r )
    {
        dat = n.normal;
        dist = d;
        _color = c;
        this.d = diff;
        this.r = r;
    }

    /+
    float intersect( ray r, float tmax )
    {
        float d = dot( dat, r.d );
        if( d != 0 )
        {
            float t = -( dot( dat, r.o ) + dist ) / d;
            if( t > 0 )
            {
                if( t < tmax )
                {
                    return t;
                }
            }
        }
        return -1.0f;
    }
    +/

    float intersect( ray r, float tmax )
    {
        float Vd = dot( r.d, N );
        if( fabs( Vd ) < 0.0000000000000001f) return -1;

        float t = ((dot( r.o, N ) + dist)/Vd);
        if( 0.0f <= t && t <= tmax )
        {
            return t;
        }

        return -1.0f;
    }

    vector normal( vector at ) 
    { 
        //if( dot( dat, at.normal ) > 0 ) return -dat;
        return dat; 
    }
    vector N() { return dat; }

    bool islight() { return false; }

    float diffuse() { return d; }
    float specular() { return 1.0f - diffuse(); }
    float reflection() { return r; }

    color Color() { return _color; }

    vector dat;
    float dist;
    color _color;
    float d, r;
}

class Light : Sphere
{
    this( vector v, color _c, float _r, float fs = 500, float fe = 1_000 ) 
    { 
        super( v, _c, _r, 0.0f, 0.0f ); 
        if( fs < fe )
        {
            fstart = fs;
            fend = fe;
        } else {
            fstart = fe;
            fend = fs;
        }
    }

    override bool islight() { return true; }

    color Color( float dist )
    {
        if( dist >= fend ) return color();
        if( dist <= fstart ) return super.Color();
        float max = fend - fstart, at = dist - fstart;
        return super.Color() * ( (max - at) / max  );
    }

    float fstart = 500, fend = 7_000;
}

class Sphere : Shape
{
    this( vector v, color _c, float _r, float diff = 1.0f, float spec = 0.0f, float refl = 0.0f ) 
    { 
        c = v; 
        r = _r; 
        _color = _c; 
        d = r*r; 
        l_diffuse = diff; 
        l_specular = spec; 
        l_reflection = refl;
    }

    float intersect( ray r, float tmax )
    {
        vector m = r.o - c;
        float b = dot( m, r.d );
        float lc = dot(m, m) - this.d;
        
        if( lc > 0.0f && b >0.0f ) return -1.0f;

        float discr = b*b - lc;
        if( discr < 0.0f ) return -1.0f;

        float t = -b - sqrt( discr );
        if( t < 0.0f || t > tmax ) return -1.0f; // near/far clipping

        return t;
    }

    vector normal( vector at )
    {
        return (at - c) * r;
    }

    bool islight() { return false; }
    float diffuse() { return l_diffuse; }
    float specular() { return 1.0f - l_diffuse; }
    float reflection() { return l_reflection; }
    color Color() { return _color; }

    vector c, _color;
    float r, d, l_diffuse, l_specular, l_reflection;
}



