module  src.state

import  src.gameobjects;

class State
    : State
{

    this( StateManager sm, GameObjects go, bool draw, bool update )
    {
        super( sm, go, draw, update );
    }

    override
    void update( float delta )
    {
        with( go ) {

        }
    }

    override
    void draw( float delta )
    {
        with( go ) {

        }
    }

    override
    void enter()
    {
        with( go ) {

        }
    }

    override
    void exit()
    {
        with( go ) {


        }
    }

}


