

#include "map.h"

U32 block_dir[] = { N_BLOCKED, E_BLOCKED, S_BLOCKED, W_BLOCKED };
U32 block_rdir[] = { S_BLOCKED, W_BLOCKED, N_BLOCKED, E_BLOCKED };

void Map::clear()
{
    if( loaded ) {
        for( IDX y = 0; y < height; ++y ) {
            //msg( y );
            if( tilemap[y] != NULL ) {
                delete[] tilemap[y];
            }
            tilemap[y] = NULL;
        }
        //msg( "done" );
        delete[] tilemap;
        tilemap = NULL;
    }

    id = width = height = 0;
    name.clear();
    npcs.clear();

    loaded = false;
}


void Map::read( FILE *fp, string &filename )
{
    MapNode     mapnode;
    MovableMapNode  npcnode;
    U32         npclen = 0;

    // clear the map
    clear();
    enforce( !loaded, "Map Loaded?" );

    // read map node
    ReadBlock( fp, filename, &mapnode );
    id = mapnode.id;
    width = mapnode.width;
    height = mapnode.height;

    // read in string
    ReadString( fp, filename, name, mapnode.strlen );

    // build tilemap
    enforce(( tilemap = new TileNode*[height] ) != NULL, strerror( errno ));
    for( IDX y = 0; y < height; ++y ) {
        tilemap[y] = new TileNode[width];
    }

    // read in map tiles
    for( IDX y = 0; y < height; ++y ) {
        for( IDX x = 0; x < width; ++x ) {
            ReadBlock( fp, filename, &(tilemap[y][x]));
        }
    }

    // read npc list size
    ReadBlock( fp, filename, &npclen );

    for( IDX i = 0; i < npclen; ++i ) {
        //ReadBlock( fp, filename, &(npcs[i] ));
        ReadBlock( fp, filename, &npcnode );
        npcs.push_back( npcnode );
    }

    cout << "Map " << name << " has " << npclen << " NPCS" << endl;

    loaded = true;
}

void Map::write( FILE *fp, string &filename )
{
    U32 npclen = npcs.size();;
    MapNode mapnode;

    enforce( loaded, "Not Loaded!" );
    cout << "Saving map to " << filename << endl;

    mapnode.id = id;
    mapnode.width = width;
    mapnode.height = height;
    mapnode.strlen = name.size();

    // write node
    WriteBlock( fp, filename, &mapnode );
    // write name
    WriteString( fp, filename, name );
    // write tiles
    for( IDX y = 0; y < height; ++y ) {
        for( IDX x = 0; x < width; ++x ) {
            WriteBlock( fp, filename, &(tilemap[y][x]));
        }
    }

    // write npclist
    WriteBlock( fp, filename, &npclen );
    for( IDX i = 0; i < npclen; ++i ) {
        WriteBlock( fp, filename, &(npcs[i]));
    }

}

TileNode & Map::operator()( U32 x, U32 y )
{
    enforce( loaded, "Map not loaded" );
    enforce( x < width, "Bad Map index: " << x << " >= " << width );
    enforce( y < height, "Bad Map index!" );
    return tilemap[y][x];
}

U32 Map::humanCount()
{
    register U32 count = 0;
    for(IDX i = 0; i < npcs.size(); i++)
    {
        if((NPC_MALE_TYPE <= npcs[i].type) && (npcs[i].type <= NPC_FEMALE_TYPE))
           count++;
    }
    return count;
}
