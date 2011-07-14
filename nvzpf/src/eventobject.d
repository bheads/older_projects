module  src.eventobject;

import  src.gameobjects;

public
alias void delegate ( DynamicObject o, EventObject e ) onHit;


class EventObject
    : StaticObject
{
    this( short _x, short _y, short width, short height, int _id,
        onHit hit )
    {
        super( _x, _y, width, height, _id );
        _hit = hit;
    }
    
    void event( DynamicObject o )
    {
        if( _hit !is null ) {
            _hit( o, this );
        }
    }  
    
    
    
     onHit _hit;
       
    
}

