/***
 * error.cpp
 *  Error codes and functions for officezombie
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#include "error.h"

string & GetError( ERRCODE code )
{
    if( code >= PK_INVALID ) {
        code = PK_INVALID;
    }
    return( ECODESTR[ code ] );
}

string ECODESTR[] = {
    "OK",

    "Config: Bad Filepointer",

    "Invalid Error Code" // this must be last
};



