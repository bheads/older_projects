module  src.aiobject;

import  src.gameobjects;

public
alias void delegate ( DynamicObject o, AIObject e ) onHitAI;
alias void delegate ( AIObject e, float delta ) onUpdateAI;


class AIObject
    : DynamicObject
{
    onHitAI     _hit;
    onUpdateAI  _update;
    int         dir = 1;
    bool        first = true;
    int         count;

    this( short _x, short _y, short width, short height, int _id,
        onHitAI hit, onUpdateAI up )
    {
        super( _x, _y, width, height, _id );
        _hit = hit;
        _update = up;
    }
    
    invariant()
    {
        assert( _id != 0 );
    }
    
    void event( DynamicObject o )
    {
        if( _hit !is null ) {
            _hit( o, this );
        }
    }  
    
    void updateai( float delta )
    {
        if( _update !is null ) {
            _update( this, delta );
        }    
    }
}

