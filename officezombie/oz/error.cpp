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
    if( code >= OZ_INVALID ) {
        code = OZ_INVALID;
    }
    return( ECODESTR[ code ] );
}

string ECODESTR[] = {
    "OK",

    "ENGINE: Failed to start",
    "ENGINE: Failed to stop",

    "INI: No dictionary loaded",
    "INI: Failed to open config file",
    "INI: File already exists",
    "INI: Failed to write to file",

    "DB: Failed to open database",
    "DB: Invalid SQL querry",

    "SFX: File Not Found",
    "SFX: Invalid Volume Value",

    "Invalid Error Code" // this must be last
};



