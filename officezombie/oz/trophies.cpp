
#include "trophies.h"

//until strings can be used in packer or a figureout how to. This data will have to be built into the engine.
string TROPHYNAMES[] = {
    "Trophy 1",
    "Trophy 2",
    "Trophy 3",
    "Invalid Trophy" // this must be last
};

string TROPHYINFO[] = {
    "Trophy 1 info",
    "Trophy 2 info",
    "Trophy 3 info",
    "Invalid Trophy" // this must be last
};

void TrophyData::clear()
{
    id = imageHash = playerStatus = 0;
}

void TrophyData::read( FILE *fp, string &filename )
{
    TrophyNode tnode;

    ReadBlock( fp, filename, &tnode );
    id = tnode.id;
    imageHash = tnode.imageHash;
    playerStatus = tnode.playerStatus;
}

void TrophyData::write( FILE *fp, string &filename )
{
    TrophyNode tnode;

    tnode.id = id;
    tnode.imageHash = imageHash;
    tnode.playerStatus = playerStatus;
    WriteBlock( fp, filename, &tnode );
}

string TrophyData::getTrophyName()
{
    return TROPHYNAMES[GD_TROPHY_ID_MIN - id];
}

string TrophyData::getTrophyInfo()
{
    return TROPHYINFO[GD_TROPHY_ID_MIN - id];
}
