module  src.state;

import  src.core;

abstract class State
{
    public:

        this( StateManager sm, Core core, bool draw, bool update )
        {
            this.sm = sm;
            this.core = core;
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
        Core            core;
}


