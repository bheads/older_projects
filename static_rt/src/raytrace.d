module src.raytrace;


import std.stdio, std.math, std.random;


import  src.vector, src.ray, src.shape;

enum depthmax = 12;

color raytrace( ray r, Shape[] shapes, float tmax = 10_000, 
        color ambiant = color( 0.05, 0.05, 0.05 ), int depth = 0 )
{
    color Color = ambiant;
    float dist = float.max, temp;
    Shape* prim = null;

    foreach( ref shape; shapes )
    {
        temp = shape.intersect( r, tmax );
        if( temp >= 0.0f && temp < dist )
        {
            dist = temp;
            prim = &shape;
        }
    }
    if( prim is null ) return Color;
    if( prim.islight ) return prim.Color();
   
    // compute ambiant light
    Color = ambiant * prim.Color();
    // find point of intersection
    vector pi = r.at( dist );
    // computer normal at pi
    vector N = prim.normal( pi ).normal;

    // find all lights
    foreach( ref lshape; shapes )
    {
        if( !lshape.islight ) continue;
        auto light = cast(Light)lshape;
        // computer vetor to light from pi
        vector L = (light.c - pi).normal;
        // find distance to light from pi
        ray lr = ray( pi, L );
        float ldist = light.intersect( lr, tmax );
        // computer shade vector
        float shade = 1.0f;
        foreach( ref shape; shapes )
        {
            // skip the light
            if( light is shape ) continue;
            // test if this shape can be hit with L and is closer the the light
            float sdist = shape.intersect( lr, tmax );
            if(  0.0f < sdist && sdist < ldist ) {
                // shape is inbetween prim and light!
                shade = 0.0f;
                break;
            }
        }
        // compute diffuse lighting
        if( prim.diffuse > 0 )
        {
            float Dot = dot( N, L );
            if( Dot > 0.0f )
            {
                float diff = prim.diffuse * Dot * shade;
                Color += diff * prim.Color * light.Color(dist);
            }
        }
        // computer specular highlights
        if( prim.specular > 0.0f )
        {
            vector V = r.d;
            vector R = L - (2.0f * N * dot( L, N ));
            float Dot = dot( V, R );
            if( Dot > 0.0f )
            {
                float spec = Dot^^20 * prim.specular * shade;
                Color += spec * light.Color(dist);
            }
        }
    }
    // compute reflection Color
    if( prim.reflection > 0.0f && depth < depthmax )
    {
        vector R = r.d - ( 2.0f * N * dot(r.d, N));
        vector O = R * 0.00001f + pi;
        auto rcol = raytrace( ray( O, R ), shapes, tmax, ambiant, depth + 1 );
        Color += prim.reflection * rcol * prim.Color();
    }
    return Color;
}


