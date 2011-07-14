module src.ray;


import src.vector;

struct ray
{
    this( ref const(ray) r )
    {
        o = r.o;
        d = r.d.normal;
    }

    this( ref vector a, ref vector b )
    {
        o = a;
        d = b.normal;
    }

    this( ref const(vector) a, ref const(vector) b )
    {
        o = a;
        d = b.normal;
    }

    const(vector) at( float t )
    {
        return o + ( t * d );
    }

    union
    {
        struct { vector o, d; }
        struct { vector origin, direction; }
    }
}
