/***
 * inireader
 *  Reads in ini files
 *
 *  Byron Heads bheads@emich.edu
 ***/

#include <fstream>
#include <sstream>

#include "inireader.h"
#include "strfunc.h"
#include "filefunc.h"

#define returncode( ERR ) { m_lasterror = ERR; return( ERR ); } 

Config::Config()
    : m_isloaded( false ), m_lasterror( 0 ), m_dictionary(), m_configfilename()
{ }

Config::Config( std::string filename )
    : m_isloaded( false ), m_lasterror( 0 ), m_dictionary(), m_configfilename()
{
    m_lasterror = load( filename );
}

Config::Config( std::string filename, bool createnew )
    : m_isloaded( false ), m_lasterror( 0 ), m_dictionary(), m_configfilename()
{
    m_lasterror = load( filename, createnew );
}

Config::~Config()
{
    if( isloaded()) clear();
}

bool Config::isloaded()
{
    return( m_isloaded );
}

ERRCODE Config::lasterror()
{
    return( m_lasterror );
}

std::string Config::configfilename()
{
    return( m_configfilename );
}

ERRCODE Config::clear()
{
    if( !isloaded()) returncode( OZ_INI_NO_DICT );
    m_dictionary.clear();

    m_isloaded = false;
    m_configfilename = "";

    returncode( OZ_OK );
}

ERRCODE Config::create( std::string filename, bool overwrite )
{
    if( isloaded()) clear(); 

    if( FileExists( filename ) && !overwrite) {
        returncode( OZ_INI_FILE_EXISTS );
    }

    m_configfilename = filename;
    m_isloaded = true;

    returncode( OZ_OK );
}

bool splitkey( const std::string &key, std::string &cat, std::string &item )
{
    size_t sep = key.find_first_of( ":" );

    if( sep == std::string::npos ) {
        return( false );
    }

    cat = key.substr( 0, sep );
    item = key.substr( sep+1 );

    trim( cat );
    trim( item );

    return( true );
}

bool matchcategory( const std::string &src, std::string &cat )
{
    size_t start = src.find_first_of( "[" );
    size_t last = src.find_last_of( "]" );
    std::string temp;

    if( start == std::string::npos || last == std::string::npos ) {
        return( false );
    }

    temp = src.substr( start+1, last-1 );
    trim( temp );
    msg( "iniread.matchcategory: temp = " << temp );
    if( !isalpha( temp[0] )) {
        return( false );
    }

    for( size_t i = 1; i < temp.length(); ++i ) {
        if( !isalpha( temp[i] ) && !isdigit( temp[i] )) {
            return( false );
        }
    }

    cat = temp;

    return( true );
}

bool matchline( const std::string &src, std::string &item, std::string &val )
{
    size_t equ = src.find_first_of( "=" );

    if( equ == std::string::npos ) {
        return( false );
    }

    item = src.substr( 0, equ );
    val = src.substr( equ + 1 );

    trim( item );
    trim( val );

    return( true );
}

ERRCODE Config::save()
{
    std::ofstream configfile;
    std::string setcategory( "Global" ), item, category;
    dictionaryiterator itemiterator;

    if( !isloaded()) returncode( OZ_INI_NO_DICT );

    configfile.open( m_configfilename.c_str());
    if( !configfile.is_open()) returncode( OZ_INI_FAILED_TO_WRITE );

    for( itemiterator = m_dictionary.begin(); itemiterator != 
            m_dictionary.end(); ++itemiterator ) {
        if( splitkey( itemiterator->first, category, item )) {
            if( setcategory != category ) {
                setcategory = category;
                configfile << "[" << category << "]" << std::endl;
            }
            configfile << item << " = " << itemiterator->second << "\n";
            
        } else {
            configfile << itemiterator->first << " = " << 
                itemiterator->second << std::endl;
        }
    }

    configfile.close();
    returncode( OZ_OK );
}

ERRCODE Config::load( std::string filename, bool createnew )
{
    std::ifstream configfile;
    std::string lineinput, category( "Global" ), item, value;
    ERRCODE ret = OZ_OK;

    if( isloaded()) clear();

    configfile.open( filename.c_str());
    if( !configfile.is_open()) {
        if( FileExists( filename ) || !createnew ) {    
            returncode( OZ_INI_FAILED_TO_OPEN );
        } else {
            return( create( filename ));
        }
    }
    m_isloaded = true;

    while( configfile.good()) {
        std::getline( configfile, lineinput );
        trim( lineinput );
        if( matchcategory( lineinput, category )) {
        } else if( matchline( lineinput, item, value )) {
            if(( ret = set( category + ":" + item, value )) != 0 ) {
                configfile.close();
                m_isloaded = false;
                returncode( ret );
            }
        }
    }

    configfile.close();
    m_configfilename = filename;
    returncode( OZ_OK );
}

U32 Config::size()
{
    return( (U32)m_dictionary.size());
}

I32 Config::get( std::string item, I32 defaultvalue, bool add )
{
    I32 returnvalue = defaultvalue;
    dictionaryiterator itemiterator = m_dictionary.find( item );

    if( itemiterator == m_dictionary.end()) {
        if( add ) set( item, defaultvalue );
    } else {
        returnvalue =  (I32)atol( itemiterator->second.c_str()  );
    }

    return( returnvalue );
}

U32 Config::get( std::string item, U32 defaultvalue, bool add )
{
    U32 returnvalue = defaultvalue;
    dictionaryiterator itemiterator = m_dictionary.find( item );

    if( itemiterator == m_dictionary.end()) {
        if( add ) set( item, defaultvalue );
    } else {
        returnvalue =  (U32)atol( itemiterator->second.c_str()  );
    }

    return( returnvalue );
}

I64 Config::get( std::string item, I64 defaultvalue, bool add )
{
    I64 returnvalue = defaultvalue;
    dictionaryiterator itemiterator = m_dictionary.find( item );

    if( itemiterator == m_dictionary.end()) {
        if( add ) set( item, defaultvalue );
    } else {
        returnvalue =  (I64)atoll( itemiterator->second.c_str()  );
    }

    return( returnvalue );
}

U64 Config::get( std::string item, U64 defaultvalue, bool add )
{
    U64 returnvalue = defaultvalue;
    dictionaryiterator itemiterator = m_dictionary.find( item );

    if( itemiterator == m_dictionary.end()) {
        if( add ) set( item, defaultvalue );
    } else {
        returnvalue =  (U64)atoll( itemiterator->second.c_str()  );
    }

    return( returnvalue );
}

F32 Config::get( std::string item, F32 defaultvalue, bool add )
{
    F32 returnvalue = defaultvalue;
    dictionaryiterator itemiterator = m_dictionary.find( item );

    if( itemiterator == m_dictionary.end()) {
        if( add ) set( item, defaultvalue );
    } else {
        returnvalue =  (F32)atof( itemiterator->second.c_str()  );
    }

    return( returnvalue );
}

F64 Config::get( std::string item, F64 defaultvalue, bool add )
{
    F64 returnvalue = defaultvalue;
    dictionaryiterator itemiterator = m_dictionary.find( item );

    if( itemiterator == m_dictionary.end()) {
        if( add ) set( item, defaultvalue );
    } else {
        returnvalue =  (F64)atof( itemiterator->second.c_str());
    }

    return( returnvalue );
}

std::string Config::get( std::string item, std::string defaultvalue, bool add )
{
    std::string returnvalue = defaultvalue;
    dictionaryiterator itemiterator = m_dictionary.find( item );

    if( itemiterator == m_dictionary.end()) {
        if( add ) set( item, defaultvalue );
    } else {
        returnvalue = itemiterator->second;
    }

    return( returnvalue );
}

bool Config::getbool( std::string item, bool defaultvalue, bool add )
{
    bool returnvalue = defaultvalue;
    dictionaryiterator itemiterator = m_dictionary.find( item );

    if( itemiterator == m_dictionary.end()) {
        if( add ) setbool( item, defaultvalue );
    } else {
        trim( itemiterator->second );
        if( iequals( itemiterator->second, std::string( "true" )) || 
                iequals( itemiterator->second, std::string( "yes" )) ||
                iequals( itemiterator->second, std::string( "1" ))) {
            returnvalue = true;
        } else if( iequals( itemiterator->second, std::string( "false" )) || 
                iequals( itemiterator->second, std::string( "no" )) ||
                iequals( itemiterator->second, std::string( "0" ))) {
            returnvalue = false;
        } else {
            returnvalue = defaultvalue;
        }
    }

    return( returnvalue );
}

ERRCODE Config::set( std::string item, I32 value )
{
    std::stringstream str;
    str << value;
    return( set( item, std::string( str.str())));
}

ERRCODE Config::set( std::string item, U32 value )
{
    std::stringstream str;
    str << value;
    return( set( item, str.str()));
}

ERRCODE Config::set( std::string item, I64 value )
{
    std::stringstream str;
    str << value;
    return( set( item, str.str()));
}

ERRCODE Config::set( std::string item, U64 value )
{
    std::stringstream str;
    str << value;
    return( set( item, str.str()));
}

ERRCODE Config::set( std::string item, F32 value )
{
    std::stringstream str;
    str << value;
    return( set( item, str.str()));
}

ERRCODE Config::set( std::string item, F64 value )
{
    std::stringstream str;
    str << value;
    return( set( item, str.str()));
}

ERRCODE Config::setbool( std::string item, bool value )
{
    return( set( item, ( value ? "true" : "false" )));
}

ERRCODE Config::set( std::string item, std::string value )
{
    if( !isloaded()) returncode( OZ_INI_NO_DICT );
    m_dictionary[ item ] = value;
    returncode( OZ_OK );
}

