

#ifndef PACKER_HASH_H
#define PACKER_HASH_H
// http://codesnippets.joyent.com/user/wastepixel/tag/hashing 

#include <string>
using namespace std;

#include "stdtype.h"
#include "error.h"

U32 djb2( string & );
U32 sdbm( string & );
U32 rs( string & );
U32 js( string & );
U32 pjw( string & );
U32 elf( string & );
U32 bkdr( string & );
U32 dek( string & );
U32 ap( string & );

#endif

