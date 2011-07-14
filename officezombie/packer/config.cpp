
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "strfunc.h"
#include "filefunc.h"

void *getU8( string &str );
void *getI8( string &str );
void *getU16( string &str );
void *getI16( string &str );
void *getU32( string &str );
void *getI32( string &str );
void *getU64( string &str );
void *getI64( string &str );
void *getF32( string &str );
void *getF64( string &str );
void *getCHAR( string &str );
void *getBOOL( string &str );
void *getSTRING( string &str );

#define VTYPEL 13
string VTYPES[] = { "U8", "I8", "U16", "I16", "U32", "I32", "U64", "I64",
    "F32", "F64", "CHAR", "BOOL", "STRING" };

ssize_t VTYPESS[] = { sizeof( U8 ), sizeof( I8 ), sizeof( U16 ), sizeof( I16 ),
    sizeof( U32 ), sizeof( I32 ), sizeof( U64 ), sizeof( I64), sizeof( F32 ), sizeof( F64 ),
    sizeof( char ), sizeof( bool ), 0 };

void *(*VTYPEF[])( string & ) = { &getU8, &getI8, &getU16, &getI16, &getU32,
    &getI32, &getU64, &getI64, &getF32, &getF64, &getCHAR, &getBOOL, 
    &getSTRING };

ERRCODE Config::load( string filename )
{
    string tmp;
    char *line = NULL;
    FILE *fp = NULL;
    size_t len = 0, linenum = 0;
    ssize_t read;

    vector<string> tokens;
    C_NODE node;
    nodes.clear();

    enforce(( fp = fopen( filename.c_str(), "r" )) != NULL,
            "Failed to read from file " << filename << ": " 
            << strerror( errno ));

    // replace with fgets
    while(( read = readline( &line, &len, fp )) != -1 ) {
        linenum++;
        tmp = line;
        trim( tmp );
        if( tmp.empty() || tmp[0] == '#' ) continue;

        node.type = NONE;
        node.list.clear();
        node.length = false;
        tokens.clear();
        stringTok( tmp, tokens );

        // test min number of tokens
        enforce( tokens.size() >= 4, 
                "Failed to parse " << filename << " ( " <<
                tokens.size() << " < 4 )\n" << linenum << ": " << line );

        // test for type
        if( tokens[0][0] == '$' ) {
            node.length = true;
            tokens[0] = tokens[0].substr( 1 );
        }

        for( size_t j = 0; j < VTYPEL; ++j ) {
            if( iequals( tokens[0], VTYPES[j] )) {
                node.type = (VTYPE)j;
                break;
            }
        }
        enforce( node.type != NONE,
                "Failed to parse " << filename << " ( \"" <<
                tokens[0] << "\" != TYPE  )\n" << linenum << ": " << line );
                
        // test for open bracket
        enforce( iequals( tokens[1], "{" ),
                "Failed to parse " << filename << " ( \"" <<
                tokens[1] << "\" != \"{\"  )\n" << linenum << ": " << line );

        for( size_t j = 2; j < tokens.size(); j++ ) {
            enforce( tokens[j][0] != '#', 
                "Failed to parse " << filename << " ( \'" <<
                tokens[j][0] << "\' == \'#\'  )\n" << linenum << ": " << line );
            if( iequals( tokens[j], "}" )) {
                if( j + 1 < tokens.size()) {
                    enforce( tokens[j+1][0] == '#',
                        "Failed to parse " << filename << " ( \'" <<
                        tokens[j][0] << "\' != \'#\'  )\n" << linenum << ": " << line );
                }
                break;
            }
            node.list.push_back( tokens[j] );
        }
        nodes.push_back(node);
    }
    fclose( fp );
    free( line );
    return PK_OK;
}

ERRCODE Config::writebin( FILE *fp )
{
    C_NODE node;
    size_t wrt;
    void *dat;

    if( fp == NULL ) {
        return PK_CONFIG_BAD_FP;
    }

    for( vector<C_NODE>::iterator node = nodes.begin(); 
            node != nodes.end(); ++node ) {
        // debug( (*node).print());
        if( (*node).length ) {
            U32 len = (*node).list.size();
            enforce( fwrite( &len, 1, sizeof(U32), fp ) == sizeof(U32), 
                    "Failed to write data to file: " << len );
        }
        for( vector<string>::iterator item = (*node).list.begin();
                item != (*node).list.end(); ++item ) {
            dat = VTYPEF[(*node).type](*item);
            wrt = (*node).type == STRING_T ? (*item).size() : VTYPESS[(*node).type];
            enforce( fwrite( dat, 1, wrt, fp ) == wrt, 
                    "Failed to write data to file: " << (*item));
            free( dat );
        }
    }

    return PK_OK;
}

void *getU8( string &str )
{
    U8 *ret = (U8*)malloc( sizeof( U8 ));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (U8)strtoul( str.c_str(), NULL, 10 );
    return (void *)ret;
}

void *getI8( string &str )
{
    I8 *ret = (I8*)malloc( sizeof( I8 ));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (I8)strtol( str.c_str(), NULL, 10 );
    return (void *)ret;
}

void *getU16( string &str )
{
    U16 *ret = (U16*)malloc( sizeof(U16));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (U16)strtoul( str.c_str(), NULL, 10 );
    return (void *)ret;
}

void *getI16( string &str )
{
    I16 *ret = (I16*)malloc( sizeof( I16 ));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (I16)strtol( str.c_str(), NULL, 10 );
    return (void *)ret;
}

void *getU32( string &str )
{
    U32 *ret = (U32*)malloc( sizeof( U32 )); 
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (U32)strtoul( str.c_str(), NULL, 10 );
    return (void *)ret;
}

void *getI32( string &str )
{
    I32 *ret = (I32*)malloc(sizeof(I32)); 
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (I32)strtol( str.c_str(), NULL, 10 );
    return (void *)ret;
}

void *getU64( string &str )
{
    U64 *ret = (U64*)malloc(sizeof(U64));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (U64)strtoull( str.c_str(), NULL, 10 );
    return (void *)ret;
}

void *getI64( string &str )
{
    I64 *ret = (I64*)malloc(sizeof(I64));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (I64)strtoll( str.c_str(), NULL, 10 );
    return (void *)ret;
}

void *getF32( string &str )
{
    F32 *ret = (F32*)malloc(sizeof(F32));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (F32)strtof( str.c_str(), NULL  );
    return (void *)ret;
}

void *getF64( string &str )
{
    F64 *ret = (F64*)malloc(sizeof(F64));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (F64)strtod( str.c_str(), NULL );
    return (void *)ret;
}

void *getCHAR( string &str )
{
    char *ret = (char*)malloc( sizeof(char));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = str[0];
    return (void *)ret;
}

void *getBOOL( string &str )
{
    bool *ret = (bool*)malloc(sizeof(bool));
    enforce( ret != NULL, "Failed to malloc: " << strerror( errno ));
    *ret = (bool)strtol( str.c_str(), NULL, 10 );
    return (void *)ret;
}

void *getSTRING( string &str )
{
    char *buf = strndup( str.c_str(), str.size());
    enforce( buf != NULL, "Failed to strdup: " << strerror( errno ));
    return (void *)buf;;
}

