/***
 * error.h
 *  Error codes and functions for officezombie
 *  Also include assert, debug and msg
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_ERROR_H
#define OZ_ERROR_H

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

#include "stdtype.h"

enum ECODE
{
    OZ_OK,

    OZ_ENGINE_FAILED_TO_START,
    OZ_ENGINE_FAILED_TO_STOP,

    OZ_INI_NO_DICT,
    OZ_INI_FAILED_TO_OPEN,
    OZ_INI_FILE_EXISTS,
    OZ_INI_FAILED_TO_WRITE,

    OZ_DB_FAILED_TO_OPEN,
    OZ_DB_EXEC_FAILED,

    OZ_SFX_FILENOTFOUND_ERROR,
    OZ_SFX_INVALID_VOLUME_VALUE,

    OZ_INVALID // this must be last
};

extern string ECODESTR[];

string & GetError( ERRCODE );


#define enforce( COND, STR ) { if( !(COND)) { cerr << "!!ENFORCE: " << __FILE__ << "(" << __LINE__ << "): [" << #COND << "]: " << STR << endl; throw( "Enforce Exception" ); }}

#ifdef EBUG
    #define assert( COND, STR ) { if( !(COND)) { cerr << "!!ASSERT: " << __FILE__ << "(" << __LINE__ << "): [" << #COND << "]: " << STR << endl; exit(-1); }}  
    #define debug( CODE ) { CODE; }
    #define msg( STR ) { cout << "MESSAGE: " << STR << endl; }
#else
    #define assert( COND, STR ) 
    #define debug( CODE ) 
    #define msg( STR ) 
#endif

#endif

