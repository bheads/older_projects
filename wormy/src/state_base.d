module  src.state

import  src.core;

class State
    : State
{

    this( StateManager sm, Core core, bool draw, bool update )
    {
        super( sm, core, draw, update );
    }

    override
    void update( float delta )
    {
        with( core ) {

        }
    }

    override
    void draw( float delta )
    {
        with( core ) {

        }
    }

    override
    void enter()
    {
        with( core ) {

        }
    }

    override
    void exit()
    {
        with( core ) {


        }
    }

}


