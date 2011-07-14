
#ifndef OZ_MOD_RESOURCE_H
#define OZ_MOD_RESOURCE_H

#include <string>
using namespace std;

#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <cstring>

#include "error.h"
#include "stdtype.h"

class ModResource
{
    public:
        ModResource( U32 _id = 0 )
            : id( _id )
        {}
        virtual ~ModResource()
        {}

        virtual void clear() = 0;
        virtual void read( FILE *, string & ) = 0;
        virtual void write( FILE *, string & ) = 0;
        U32 ID() { return id; }
        U32 ID( U32 _id ) { return( id = _id ); }

    protected:
        U32 id;

        template <class T> 
        void ReadBlock( FILE *fp, string &filename, T *block )
        {
            enforce( fread( block, 1, sizeof( T ), fp ) == sizeof( T ),
                    "Failed to read block from " << filename << " [ " << 
                    strerror( errno ) );
        }

        template <class T> 
        void WriteBlock( FILE *fp, string &filename, T *block )
        {
            enforce( fwrite( block, 1, sizeof( T ), fp ) == sizeof( T ),
                    "Failed to write block to " << filename << " [ " << 
                    strerror( errno ) );
        }

        void ReadString( FILE *, string &, string &, U32 );
        void WriteString( FILE *, string &, string & );

};

#endif

