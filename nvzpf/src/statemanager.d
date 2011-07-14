module  src.statemanager;

import  std.stdio;

import src.state;

class StateManager
{
    public:

        void update( float delta )
        {
            if( empty ) return;
            foreach_reverse( s; data ) {
                s.update( delta );
                if( s.StopUpdate ) break;
            }
        }

        void draw( float delta )
        {
            if( empty ) return;
            int idx;
            foreach_reverse( i, s; data ) {
                if( s.StopDraw() ) {
                   foreach( j, st; data[i..$] ) {
                        debug writeln( "Drawing state ", j );
                        st.draw( delta );
                        debug writeln( "OK" );
                   }
                   break;
                }
            }
            
            
        }

        void push( State s )
        {
            assert( s, "Pushed a null state" );
            data ~= s;
            s.enter();
        }

        void pop()
        {
            //debug writeln( "\t\t\tPoping State" );
            if( empty ) return;
            auto s = data[$-1];
            data = data[0..$-1];
            s.exit();
            //debug writeln( "\t\t\tOK" );
        }

        bool empty() { return data.length == 0; }

        void clear()
        {
            foreach_reverse( s; data ) {
                s.exit();
            }
        }

    private:
        State[] data;
}


