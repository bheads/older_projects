
#include "rand.h"


Random::Random()
{
    static bool once = true;
    if( once ) {
        srand( time(0));
        once = !once;
    }
}

I32 Random::nextInt( I32 min, I32 max )
{
   return ( rand() % ( max - min ) + min ); 
}

