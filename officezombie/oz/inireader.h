/***
 * inireader
 *  Reads in ini files
 *
 *  Byron Heads bheads@emich.edu
 ***/

#ifndef INIREADER_H
#define INIREADER_H

#include <map>
#include <string>

#include "stdtype.h"
#include "error.h"


typedef std::map<std::string, std::string> dictionary;
typedef std::map<std::string, std::string>::iterator dictionaryiterator;

class Config
{
    public:
        Config();
        Config( std::string filename );
        Config( std::string filename, bool createnew );
        virtual ~Config();

        bool isloaded();
        ERRCODE lasterror();
        std::string configfilename();
        void setfilename( std::string filename );
        ERRCODE clear();

        ERRCODE load( std::string filename, bool createnew = false );
        ERRCODE create( std::string filename, bool overwrite = false );
        ERRCODE save();

        U32 size();

        I32 get( std::string item, I32 defaultvalue, bool add = false );
        U32 get( std::string item, U32 defaultvalue, bool add = false );
        I64 get( std::string item, I64 defaultvalue, bool add = false );
        U64 get( std::string item, U64 defaultvalue, bool add = false );
        F32 get( std::string item, F32 defaultvalue, bool add = false );
        F64 get( std::string item, F64 defaultvalue, bool add = false );
        std::string get( std::string item, std::string defaultvalue, bool add = false );
        bool getbool( std::string item, bool defaultvalue, bool add = false );

        ERRCODE set( std::string item, I32 value );
        ERRCODE set( std::string item, U32 value );
        ERRCODE set( std::string item, I64 value );
        ERRCODE set( std::string item, U64 value );
        ERRCODE set( std::string item, F32 value );
        ERRCODE set( std::string item, F64 value );
        ERRCODE set( std::string item, std::string value );
        ERRCODE setbool( std::string item, bool value );

    private:
        bool        m_isloaded;
        ERRCODE     m_lasterror;
        dictionary  m_dictionary;
        std::string m_configfilename;
}; 

#endif

