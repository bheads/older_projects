module src.main;

import std.stdio, std.random, std.conv, std.datetime, std.string;


import src.image, src.onb, src.vector, src.ray, src.shape, src.raytrace, src.camera, src.matrix;

void main()
{

    StopWatch sw;
    sw.start();
    Image img = Image( 1024, 1024 );
    float hw = img.cols/2, hh = img.rows/2;
    Shape[] shapes;

    auto do_random = true;

    if( do_random )
    {
        foreach( i ; 0..80) {
                shapes ~= new Sphere( 
                    vector( uniform(-hw, hw), uniform( -hh, hh ), 
                        uniform( -200, -60 )), 
                    vector( uniform(0.0f,1.0f), uniform(0.0f,1.0f), uniform(0.0f,1.0f)),
                    uniform(5,50),  uniform(0.0f, 1.0f), 0.0f, uniform( 0.0f, 1.0f));
        }

        foreach( i ; 0..8) {
            float ls = 1.0f;
            shapes ~= new Light( 
                    vector( uniform(-hw, hw), uniform( -hh, hh ), 
                uniform( -100, -1 )), 
                vector(ls,ls,ls),
                2,//uniform(0.000001,0.000002),
                uniform( 700, 1500 ), uniform( 1000, 3000 ));
        }

        //shapes ~= new Plane( 0, 0, 1, 250, color(1,1,1));
        //shapes ~= new Plane2( vector( 0,0, -250), vector( 0,0.05,1), color( 1,1,1), 0.01, 1 );
        shapes ~= new Plane( vector( 0,0.05, 1), -2000, color( 1,1,1), 0, 1 );
    } else {

        shapes ~= new Light( vector( -200, 100, -200 ), vector(1,1,1), 
                1, 1120, 2_250 );
        shapes ~= new Light( vector( 180, -210, -250 ), vector(1,1,1), 
                1, 1000, 2_360 );
        shapes ~= new Light( vector( 0, 0, 0 ), vector(1,1,1), 
                1, 1_500, 10_000 );

        shapes ~= new Sphere( vector( 0,0,-320), vector( 1,1,1),
                50,  0.01f, 0.9f, 1.0f );

        shapes ~= new Sphere( vector( -150, 150,-325), vector( 0,1,0), 50,  0.0f, 0.5f, 0.9f );
        shapes ~= new Sphere( vector( -150, -150,-325), vector( 1,1,0), 50,  0.0f, 0.5f, 0.9f );
        shapes ~= new Sphere( vector( 150, -150,-325), vector( 0,1,1), 50,  0.0f, 0.5f, 0.9f );
        shapes ~= new Sphere( vector( 150, 150,-325), vector( 1,0,1), 50,  0.0f, 0.5f, 0.9f );

        //shapes ~= new Plane( 0, 0, -1, -150, color(1,1,1));
        //shapes ~= new Plane( 1, 0,  0, 0, color(1,0,0));
        //shapes ~= new Plane2( vector( 0,0, -1_000), vector( 0,0.05,1), color( 1,1,1), 0, 1 );
        //shapes ~= new Plane2( vector( 0,0, -200), vector( 0,0.05,1), color( 1,1,1), 0, 1 );
        //shapes ~= new Plane( vector( 0,0.01, 1), -1000, color( 1,1,1), 0, 1 );
  //      shapes ~= new Plane( vector( 0,0.0, -1), 300, color( 1,1,1), 0, 1 );
/+
        shapes ~= new Plane( vector( 1,0, 0), -300, color( 1,1,1), 0, 1 );
        shapes ~= new Plane( vector( -1,0,0), 300, color( 1,1,1), 0, 1 );

        shapes ~= new Plane( vector( 0, 1, 0), -300, color( 1,1,1), 0, 1 );
        shapes ~= new Plane( vector( 0, -1,0), 300, color( 1,1,1), 0, 1 );
+/
        vector a = vector( 0, -300, -650 );
        vector b = vector( 300, -300, -350 );
        vector c = vector( 300, 300, -350 );
        vector d = vector( 0, 300, -650 );
        vector e = vector( -300, -300, -350 );
        vector f = vector( -300, 300, -350 );

        shapes ~= new Triangle( a, b, c, color( 1,1,1), 0, 1 );
        shapes ~= new Triangle( c, d, a , color( 1,1,1), 0, 1 );

        shapes ~= new Triangle( e, a, d, color( 1,1,1), 0, 1 );
        shapes ~= new Triangle( d, f, e , color( 1,1,1), 0, 1 );
        //shapes ~= new Triangle( vector( 300,300,-310), vector( 300, 100, -310 ),
        //        vector( 100, 100, -310 ), color( 0,1,0), 0, 1 );
    }

    Camera cam = Camera( 
            vector( 0, 0, 0 ),
            vector( 0, 0, -1 ),
            vector( 0, 1, 0 ), img.cols, img.rows );

    for( size_t row = 0; row < img.rows; ++row )
    {
        for( size_t col = 0; col < img.cols; ++col )
        {
            img.raster[img.rows-row-1][col] = 
                sample( cast(float)col, cast(float)row, shapes, cam );
            writef( "\b\b\b\b\b\b\b\b\b%03.4f%%", 
                    100.0f * (cast(float)(row*img.cols + col) / cast(float)(img.rows*img.cols)));
            stdout.flush();
        }
    }
    writeln();
    
    auto now = Clock.currTime;
    sw.stop();
    double time = sw.peek.msecs / 1000.0;
    auto unit = "s";
    if( time > 60.0 ) {
        time /= 60.0;
        unit = "m";
    }
    writeln( "Took ", time, unit );

    img.writePPM( format( "img/rt.%04d%02d%02d_%02d%02d%02d_%f%s.ppm", now.year, now.month, 
                now.day, now.hour, now.minute, now.second, time, unit ));
}

color sample( float x, float y, Shape[] shapes, Camera cam )
{
    color c;
    uint samples;
    c += raytrace( cam.getray(x,y), shapes, 10_000  );
    for( float yo = 0; yo < 1.0f; yo += uniform( 0.1f, 0.50001f ))
    {
        for( float xo = 0; xo < 1.0f; xo += uniform( 0.1f, 0.50001f ))
        {
            ++samples;
            c += raytrace( cam.getray(x+xo,y+yo), shapes, 10_000  );
       }
    }
    return c / samples;
}

