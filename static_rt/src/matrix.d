module src.matrix;


import std.math, std.conv, std.stdio;

import src.vector;



struct matrix
{

    this( matrix m )
    {
        cell = m.cell.dup;
        width = m.width;
        height = m.height;
    }

    this( vector v )
    {
        width = v.cell.length;
        height = 1;
        cell = new float[][]( height, width );
        writeln( cell.length);
        cell[0][] = v.cell[];
    }

    this( float[][] v )
    {
        cell = v.dup;
        height = cell.length;
        if( height > 0 ) width = cell[0].length;
    }

    this( uint x, uint y )
    {
        width = x; height = y;
        cell = new float[][](height,width);
    }

    float[] opIndex( uint y )
    {
        if( y >= height ) throw new Exception( "Bad row index: " ~ to!string(y) ~ " >= " ~ to!string( height ) );
        return cell[y];
    }

    float opIndex( uint x, uint y )
    {
        if( x >= width || y >= height ) throw new Exception( "Bad index" );
        return cell[y][x];
    }

    void opIndexAssign( float[] r, uint y )
    {
        if( y >= height ) throw new Exception( "Bad row index" );
        cell[y][] = r[];
    }
    void opIndexAssign( vector v, uint y )
    {
        if( y >= height ) throw new Exception( "Bad row index" );
        if( width != v.cell.length ) throw new Exception( "Width != vector width" );
        cell[y][] = v.cell[];
    }

    void opIndexAssign( float v, uint x, uint y )
    {
        if( x >= width || y >= height ) throw new Exception( "Bad index" );
        cell[y][x] = v;
    }

    void opIndexOpAssign(  string op )( float[] v,  uint y )
        if( op == "+" || op == "-" || op == "*" || op == "/" || op == "" )
    {
        if( y >= height ) throw new Exception( "Bad row index" );
        mixin( "cell[y][] " ~ op ~ "= v[];" );
    }

    void opIndexOpAssign(  string op )( float v,uint x, uint y )
        if( op == "+" || op == "-" || op == "*" || op == "/" || op == "" )
    {
        if( x >= width || y >= height ) throw new Exception( "Bad index" );
        mixin( "cell[y][x] " ~ op ~ "= v;" );
    }

    matrix opBinary( string op )( matrix m ) 
        if( op == "+" || op == "-" || op == "" )
    {
        if( width != m.width || height != m.height ) 
            throw new Exception( "Matrix must be same dimensions" );
        matrix ret = cell;
        for( uint y; y < height; ++y )
                mixin( "ret[y] " ~ op ~ "= m[y];" );
        return ret;
    }

    matrix opBinary( string op )( matrix m ) 
        if(op == "*" )
    {
        if( width != m.height ) 
            throw new Exception( "Matrix width must match height to multiply" );
        matrix ret = matrix( m.width, height );
        for( uint i = 0; i < height; ++i )
            for( uint j = 0; j < m.width; ++j )
            {
                ret.cell[i][j] = 0.0f;
                for( uint k = 0; k < width; ++k )
                {
                    ret.cell[i][j] += cell[i][k]*m.cell[k][j];
             
                }
            }

        return ret;
    }

    matrix opBinary( string op )( float v ) 
        if( op == "+" || op == "-" || op == "" || op == "*" || op == "/" )
    {
        matrix ret = cell;
        for( uint y; y < height; ++y )
                mixin( "ret.cell[y][] " ~ op ~ "= v;" );
        return ret;
    }

    ref matrix opOpAssign( string op )( matrix m ) 
        if( op == "+" || op == "-" || op == "" )
    {
        if( width != m.width || height != m.height ) 
            throw new Exception( "Matrix must be same dimensions" );
        foreach( uint i, ref float[] row; cell )
            mixin( "row[] " ~ op ~ "= m.cell[i][]; " );
        return this;
    }

    ref matrix opOpAssign( string op )( float  v ) 
        if( op == "+" || op == "-" || op == "" || op == "*" || op == "/" )
    {
        foreach( uint i, ref float[] row; cell )
            mixin( "row[] " ~ op ~ "= v; " );
        return this;
    }

    matrix T()
    {
        matrix ret = matrix( height, width );
        for( uint i = 0; i < height; ++i )
            for( uint j = 0; j < width; ++j )
                ret.cell[j][i] = cell[i][j];
        return ret;
    }

    string toString()
    {
        string ret;
        foreach( ref row; cell )
        {
            ret ~= "[ ";
            foreach( v; row )
                ret ~= to!string( v ) ~ " " ;
            ret ~= "]\n";
        }
        
        return ret;
    }

    float cell[][];
    uint width, height; 

}

