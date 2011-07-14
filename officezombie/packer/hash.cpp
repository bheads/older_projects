
#include "hash.h"

U32 djb2( string &str )
{
	U32 hash = 5381;

    enforce( str.length() > 0, "Cannot hash empty strings" );
    for( size_t i = 0; i < str.length(); ++i ) {
        hash = (( hash << 5 ) + hash ) + static_cast<U32>(str[i]);
    } 

    return( hash & 0x7FFFFFFF );
}

U32 sdbm( string &str )
{
    U32 hash = 0;

    enforce( str.length() > 0, "Cannot hash empty strings" );
    for( size_t i = 0; i < str.length(); ++i ) {
        hash = static_cast<U32>(str[i]) + ( hash << 6 ) + ( hash << 16 ) - hash;
    } 

    return( hash & 0x7FFFFFFF );
}

U32 rs( string &str )
{
    U32 hash = 0, a = 378551, b = 63689;

    enforce( str.length() > 0, "Cannot hash empty strings" );
    for( size_t i = 0; i < str.length(); ++i ) {
        hash = hash * a + static_cast<U32>(str[i]);
        a *= b;
    } 

    return( hash & 0x7FFFFFFF );
}

U32 js( string &str )
{
	U32 hash = 1315423911;

    enforce( str.length() > 0, "Cannot hash empty strings" );
    for( size_t i = 0; i < str.length(); ++i ) {
        hash ^= (( hash << 5 ) + static_cast<U32>(str[i]) + ( hash >> 2 ));
    } 

    return( hash & 0x7FFFFFFF );
}

U32 pjw( string &str )
{
    U32 bui = (U32)( sizeof(U32) * 8 );
    U32 tq  = (U32)(( bui * 3 ) / 4 );
    U32 oe  = (U32)( bui / 8 );
    U32 hb  = (U32)( 0xFFFFFFFF ) << ( bui - oe );
	U32 hash = 0, test = 0;

    enforce( str.length() > 0, "Cannot hash empty strings" );
    for( size_t i = 0; i < str.length(); ++i ) {
        hash = ( hash << oe ) + static_cast<U32>(str[i]);
        if(( test = hash * hb ) != 0 ) {
            hash = (( hash ^ ( test >> tq )) & ( ~hb ));
	}
    } 

    return( hash & 0x7FFFFFFF );
}

U32 elf( string &str )
{
	U32 hash = 0, x = 0;

    enforce( str.length() > 0, "Cannot hash empty strings" );
    for( size_t i = 0; i < str.length(); ++i ) {
        hash = ( hash << 4 ) + static_cast<U32>(str[i]);
        if(( x = hash & 0xF0000000L ) != 0 ) {
            hash ^= ( x >> 24 );
            hash &= ~x;
        }
    } 

    return( hash & 0x7FFFFFFF );
}

U32 bkdr( string &str )
{
	U32 hash = 0, seed = 131; // 31 131 1313 13131 131313 ...

    enforce( str.length() > 0, "Cannot hash empty strings" );
    for( size_t i = 0; i < str.length(); ++i ) {
        hash = ( hash * seed ) + static_cast<U32>(str[i]);
    } 

    return( hash & 0x7FFFFFFF );
}

U32 dek( string &str )
{
	U32 hash = static_cast<U32>( str.length());

    enforce( str.length() > 0, "Cannot hash empty strings" );
    for( size_t i = 0; i < str.length(); ++i ) {
        hash = (( hash << 5 ) ^ ( hash >> 27 )) ^ static_cast<U32>(str[i]);
        
    } 

    return( hash & 0x7FFFFFFF );
}

U32 ap( string &str )
{
	U32 hash = 0;

    enforce( str.length() > 0, "Cannot hash empty strings" );
    for( size_t i = 0; i < str.length(); ++i ) {
        hash ^= (( i & 1 )== 0 ) ? (( hash << 7 ) ^ static_cast<U32>(str[i]) ^ 
                                ( hash >> 3 )) :
                                ( ~(( hash << 11 ) ^ static_cast<U32>(str[i]) ^ 
                                ( hash >> 5 )));
    } 

    return( hash & 0x7FFFFFFF );
}













