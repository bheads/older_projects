

#ifndef PK_CONFIG_H
#define PK_CONFIG_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "error.h"
#include "stdtype.h"

#define MAGIC_KEY (U32)17760099

enum VTYPE
{
    U8_T = 0,
    I8_T,
    U16_T,
    I16_T,    
    U32_T,
    I32_T,
    U64_T,
    I64_T,
    F32_T,
    F64_T,
    CHAR_T,
    BOOL_T,
    STRING_T,
    NONE
};

extern string VTYPES[];
extern ssize_t VTYPESS[];

struct C_NODE
{
    VTYPE type;
    vector<string> list;
    bool length;

    C_NODE()
        : type( NONE ), list(), length( false )
    {}

    C_NODE( const C_NODE &n )
        : type( n.type ), list( n.list ), length( n.length )
    {}

    C_NODE( C_NODE &n )
        : type( n.type ), list( n.list ), length( n.length )
    {}


    ~C_NODE() {}

    void print() {
        cout << "NODE: " << ( length ? "$": " " );
        cout << VTYPES[ type ] << "(" << VTYPESS[ type ] << ")";
        cout << " { ";
        if( length ) cout << "(" << list.size() << ") ";
        for( size_t i = 0; i < list.size(); ++i ) {
            cout << list[i] << " ";
        }
        cout << " } " << endl;
    }

};

class Config
{
    public:
        Config()
            : nodes()
        {}
        
        ~Config(){}

        ERRCODE load( string );
        ERRCODE writebin( FILE * );

    private:
        vector<C_NODE> nodes;


};

#endif

