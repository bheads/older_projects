
#ifndef OZ_TROPHIES_H
#define OZ_TROPHIES_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include "mod_resource.h"
#include "defaults.h"

struct TrophyNode {
    U32 id;
    U32 imageHash;
    U32 playerStatus;
};

class TrophyData
    : public ModResource
{
    public:

        TrophyData( )
            : ModResource( 0 )
        {}

        void clear();
        void read( FILE *, string & );
        void write( FILE *, string & );

        string getTrophyName();
        string getTrophyInfo();

        U32 imageHash;
        U32 playerStatus;
};

#endif
