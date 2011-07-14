/***
 * strfunc
 *  collection of useful string functions
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/


#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "strfunc.h"
#include "stdtype.h"


#ifdef POSIX
#else
char* strndup(const char *s, size_t n) {
    char *p = (char *)malloc(strlen(s) + 1);
    if(p) { strcpy(p, s); }
    return p;
}
#endif

#ifdef OSX
char* strndup(const char *s, size_t n) {
    char *p = (char *)malloc(strlen(s) + 1);
    if(p) { strcpy(p, s); }
    return p;
}
#endif

void trim( std::string &str )
{
    size_t front = 0, back = str.size() - 1;
    while( front < str.size() && back >= 0 &&
            ( isspace( str[front] ) || isspace( str[back] ))) {
        if( isspace( str[front] )) ++front;
        if( isspace( str[back] )) --back;
    }

    str = str.substr( front, 1 + back - front );

}

bool iequals( const std::string &lhs, const std::string &rhs )
{
    if( lhs.length() != rhs.length()) {
        return( false );
    }

    for( size_t i = 0; i < lhs.length(); ++i ) {
        char a = tolower( lhs[i] );
        char b = tolower( rhs[i] );
        if(  a != b ) {
            return( false );
        }
    }

    return( true );
}

// String tokenizer. Returns into passed string vector.
void stringTok(std::string &str, std::vector<std::string> &list)
{
	size_t start = 0;
	size_t end = 0;
	std::string temp;

	while(end < str.size() && isspace(str[end])) {
		end++;
    }
	start = end;

	while(end < str.size())
	{
		end++;
		if(isspace(str[end]))
		{
			temp = str.substr(start, end-start);
			trim(temp);
			list.push_back(temp);
			while(end < str.size() && isspace(str[end])) {
				end++;
            }
			start = end;
		}
	}

    if( end > start ) {
        temp = str.substr(start, end-start);
        trim(temp);
        list.push_back(temp);
    }
}


void stringSep( std::string &str, std::vector<std::string> &list, char sep )
{
    std::string tmp;
    for( IDX start = 0, end = 0; end <= str.size(); ++end ) {
        if(( end + 1 ) > str.size() || str[end] == sep ) {
            if( end > start ) {
                tmp = str.substr( start, end - start );
                trim( tmp );
                if( tmp.size() > 0 ) {
                    list.push_back( tmp );
                }
            }
            start = end + 1;
        } 
    }
}

bool contains( std::string &str, char c )
{
    for( size_t i = 0; i < str.size(); ++i ) {
        if( str[i] == c ) return true;
    }

    return false;
}

