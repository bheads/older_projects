module  src.graphics;

import  std.string,
        std.conv,
        std.exception,
        std.math;


import  src.sdl,
        src.core;


class Graphics
{

    @property surface screen() { return _screen; }
    @property void screen( surface s ) { _screen =s; }

    this()
    {
        font = enforce( TTF_OpenFont( "font.ttf", 18 ), mixin( TTF_EX ));
    }
    
    ~this()
    {
        //TTF_CloseFont( font );
    }

    surface loadimg( string file, uint colorkey = 0xff00ff )
    {
        version( Windows ) {
            file = file.replace( "/", "\\" );
        }

        surface ret;
        surface tmp = enforce( IMG_Load( toStringz( file )), mixin( IMG_EX ));
        scope(exit) SDL_FreeSurface( tmp );
        ret = enforce( SDL_DisplayFormat( tmp ), mixin( SDL_EX ));
        enforce( !SDL_SetColorKey( ret, SDL_SRCCOLORKEY, colorkey ), mixin( SDL_EX ));
        return ret;
    }
    
    void line( surface surf, int x0, int y0, int x1, int y1, uint color )
    {
        enforce( !SDL_LockSurface( surf ), mixin( SDL_EX ));
        scope( exit ) SDL_UnlockSurface( surf );
      
        int dy = y1 - y0;
        int dx = x1 - x0;
        float t = 0.5f;                     

        (cast(uint*)surf.pixels)[ y0 * surf.w + x0] = color;
        if( abs(dx) > abs(dy)) {        
            float m = cast(float) dy / cast(float) dx;     
            t += y0;
            dx = (dx < 0) ? -1 : 1;
            m *= dx;
            while (x0 != x1) {
                x0 += dx;                           
                t += m;                             
                (cast(uint*)surf.pixels)[ cast(int)t * surf.w + x0] = color;
            }
        } else {                                   
            float m = cast(float) dx / cast(float) dy;     
            t += x0;
            dy = (dy < 0) ? -1 : 1;
            m *= dy;
            while (y0 != y1) {
                y0 += dy;                           
                t += m;                             
                (cast(uint*)surf.pixels)[ y0 * surf.w + cast(int)t] = color;
            }
        }
    } 
    
    /*double dist( StaticObject a, StaticObject b )
    {
        return sqrt( (cast(double)a.x - b.x )^^2.0 + ( cast(double)a.y - b.y ) ^^ 2.0 );
    }*/

    void box( surface surf, short x, short y, ushort w, ushort h, uint color = 0 )
    {
        rect r;
        r.x = x; r.y = y;
        r.w = w; r.h = h;
        enforce( !SDL_FillRect( surf, &r, color ), mixin( SDL_EX ));
    }

    void clear( surface surf,  rect *r = null, uint color = 0x000000 )
    {
        enforce( !SDL_FillRect( surf, r, color ), mixin( SDL_EX ));
    }

    void clear()
    {
        enforce( !SDL_FillRect( screen, null, 0x000000 ), mixin( SDL_EX ));
    }

    void flip()
    {
        enforce( !SDL_Flip( screen ), mixin( SDL_EX ));
    }

    void blit( surface src, rect *srcrect, surface dst, rect* dstrect )
    {
        enforce( !SDL_BlitSurface( src, srcrect, dst, dstrect ), mixin( SDL_EX ));
    }

    void blit( surface src, rect srcrect, surface dst, rect dstrect )
    {
        enforce( !SDL_BlitSurface( src, &srcrect, dst, &dstrect ), mixin( SDL_EX ));
    }

    surface gettext( string text, ubyte r, ubyte g, ubyte b )
    {
        SDL_Color  color = { r, g, b };
        return enforce( TTF_RenderUTF8_Solid( font, toStringz( text ), color ),
                                mixin( TTF_EX ));
    }
    
    private:
        surface _screen;
        TTF_Font* font;
}


