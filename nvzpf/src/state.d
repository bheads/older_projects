module  src.state;

import  src.gameobjects;

abstract class State
{
    public:

        this( StateManager sm, GameObjects go, bool draw, bool update )
        {
            this.sm = sm;
            this.go = go;
            StopDraw( draw );
            StopUpdate( update );
        }

        void update( float delta);
        void draw( float delta );
    
        void enter();
        void exit();

        @property bool StopDraw() { return stopdraw; }
        @property bool StopUpdate() { return stopupdate; }

        @property typeof(this) StopDraw( bool v ) 
        { 
            stopdraw = v;  
            return this; 
        }

        @property typeof(this) StopUpdate( bool v ) 
        { 
            stopupdate = v;  
            return this; 
        }

    protected:
        bool    stopdraw;
        bool    stopupdate;

        StateManager    sm;
        GameObjects     go;
}


