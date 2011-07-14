
#ifndef OZ_MOVABLE_NODE_H
#define OZ_MOVABLE_NODE_H

#include "stdtype.h"

enum Direction
{
    North   = 0,
    East    = 1,
    South   = 2,
    West    = 3
};

enum MovableType
{
    NPC_MALE_TYPE       = 0,
    NPC_FEMALE_TYPE     = 1,

    ZOMBIE_MALE_TYPE    = 10,
    ZOMBIE_FEMALE_TYPE  = 11,

    CHAIR_TYPE          = 20,
    BOX_TYPE            = 21,
    FILE_TYPE           = 22,
    DESK_TYPE           = 23,

    RAT_TYPE            = 30,
    MEAT_TYPE           = 31,
    PAPER_TYPE          = 32,

    PUZZLE_TYPE         = 40,
    EVENT_TYPE         = 41,

    PLAYER_TYPE         = 50,
    UNKNOWN_TYPE
};


struct MovableNode
{
    U32 id;
    U32 n_hash, e_hash, s_hash, w_hash;
    U32 sn_hash, se_hash, ss_hash, sw_hash;
};

struct MovableMapNode
{
    U32 movable_id;
    I32 x, y;
    U32 direction;
    U32 alive;
    U32 type;
    U32 mutable_id;

    MovableMapNode()
        : movable_id( 0 ), x( 0 ), y( 0 ), direction( North ), alive( true ),
        type( NPC_MALE_TYPE ), mutable_id( 0 )
    {}
};



#endif

