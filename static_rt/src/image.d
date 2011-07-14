module src.image;

import std.stdio;

import src.vector;


struct Image
{
    this( Image img )
    {
        cols = img.cols;
        rows = img.rows;
        raster = img.raster.dup;
    }

    this( uint c, uint r )
    {
        this( c, r, color( 0, 0, 0 ));
    }

    this( uint c, uint r, color bg )
    {
        cols = c;
        rows = r;
        raster = new color[][](r,c);
        foreach( ref row; raster ) {
            foreach( ref _color; row ) {
                _color = bg;
            }
        }
    }

    bool set( uint x, uint y, color c )
    {
        if( x >= cols || y >= rows ) return false;
        raster[y][x] = c;
        return true;
    }

    void writePPM( string filename )
    {

        auto f = File( filename, "w" );
        f.writef( "P6\n%d %d\n255\n", cols, rows );

        foreach( ref row; raster ) {
            foreach( ref c; row ) {
                c.clamp;
                f.writef("%r%r%r", c.R, c.G, c.B);
            }
        }

        f.close();
    }

    uint        cols, rows;
    color[][]   raster;
}
