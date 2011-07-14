

#include "images.h"


Image & ImageManager::get( U32 hash )
{

    U8 *data;
    U32 size;

    // test if images is load, else stream it in
    if( images.find( hash ) == images.end()) {
        data = packman.getNEWdata( hash, size );
        images[ hash ].LoadFromMemory( (char *)data, size );
        delete[] data; 
    }

    return( images[ hash ] );

}
