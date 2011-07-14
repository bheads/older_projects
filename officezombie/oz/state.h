
/***
 * State 
 *  Interface used by the state manager
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_STATE_H
#define OZ_STATE_H

#include "stdtype.h"
#include "error.h"

class State
{
    public:
        State( bool blogic = true, bool brender = true) 
            : m_blocklogic( blogic ), m_blockrender( brender )
        {}
        ~State() {};

        virtual void init() = 0;
        virtual void deinit() = 0;
        virtual void logic( F32 delta ) = 0; 
        virtual void render() = 0;
        virtual void paused() = 0;
        virtual void unpaused() = 0;

        bool blocklogic() { return( m_blocklogic ); }
        bool blockrender() { return( m_blockrender ); }

    protected:
        bool    m_blocklogic, m_blockrender;
};

#endif

