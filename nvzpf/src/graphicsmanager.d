module  src.graphicsmanager;


import  src.sdl,
        src.graphics,
        src.manager;

public
import  src.gfx_id;


class GraphicsManager
    : Manager!(  int, surface )
{
    public:
        this( Graphics _gfx )
        {
            gfx = _gfx;
        }
        

        void load( int key, string file )
        {
            if( key in data ) return;
            set( key, gfx.loadimg( file ));            
        }

        override void clear()
        {
            foreach( key, surf; data ) {
                SDL_FreeSurface( surf );
            }
        }


    private:
        Graphics gfx;

}


