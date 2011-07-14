module src.camera;

import std.math, std.stdio;

import src.vector, src.ray;


struct Camera
{
    this( vector e, vector l, vector u, float w, float h, float dist = 1.0f )
    {
        eye = e;
        lookat = l;
        up = u;
        right = cross( up, lookat );
        width = w;
        height = h;

        fovx = PI/4.0f;
        theta = fovx/2.0f;;
        distance = dist;
        tfovx = tan( fovx );
        //fovy = ( width / height ) * fovx;
        fovy = ( height / width ) * fovx;
        tfovy = tan( fovy );

        pixelWidth = 2 * tan( fovx/2) * dist/width;
        pixelHeight = 2 * tan( fovy/2) * dist/height;
    }

    ray getray( float u, float v )
    {
        return ray( vector( u - width/2, v-height/2, 50 ), vector( 0,0,-1 ));
        //-255 just a made up fov
        vector dir = [ u - width/2, v - width/2, -255, 0 ];
        dir.normalize;
        return ray( eye, dir );
    }


        /+
    ray getray( float u, float v )
    {

        float x = ((2*u - width)/width) * tfovx;
        float y = ((2*v - height)/height) * tfovy;
        vector dir = vector( x, y, -1 );
        dir.normalize;
        return ray( eye, dir);
    }
    +/


    vector eye, lookat, up, right;
    float width, height;
    float fovx, fovy, tfovx, tfovy, theta, distance;
    float pixelWidth, pixelHeight;
}
