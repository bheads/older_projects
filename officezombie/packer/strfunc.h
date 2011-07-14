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

void trim( std::string & );
bool iequals( const std::string &, const std::string & );

void stringTok(std::string &, std::vector<std::string> &);
void stringSep( std::string &, std::vector<std::string> &, char );
bool contains( std::string &, char );


#ifdef POSIX
#else
char* strndup(const char *, size_t );
#endif

#ifdef OSX
char* strndup(const char *, size_t );
#endif


#endif


