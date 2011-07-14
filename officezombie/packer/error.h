/***
 * error.h
 *  Error codes and functions for officezombie
 *  Also include assert, debug and msg
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef PK_ERROR_H
#define PK_ERROR_H

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

#include "stdtype.h"

enum ECODE
{
    PK_OK,

    PK_CONFIG_BAD_FP,

    PK_INVALID // this must be last
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

