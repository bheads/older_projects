/***
 * strfunc.h
 *  collection of useful string functions
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/


#ifndef STRFUNC_H
#define STRFUNC_H

#include <vector>
#include <string>
#include "stdtype.h"

void trim( std::string & );
bool iequals( const std::string &, const std::string & );

void stringTok(std::string &, std::vector<std::string> &);

void stringAppend(std::string&, U32);


#ifdef POSIX
#else
char* strndup(const char *, size_t );
#endif

#endif


