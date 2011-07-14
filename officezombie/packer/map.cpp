


#include <cerrno>

#include "map.h"


U32 convert( string &str )
{
    return (U32)strtoul( str.c_str(), NULL, 10 );
}

F32 fconvert( string &str )
{
    return (F32)strtof( str.c_str(), NULL );
}

U32 convert( const char *str )
{
    return (U32)strtoul( str, NULL, 10 );
}

void Map::clear()
{
    id = width = height = 0;
    hloaded = false;
    tilemap.clear();
    npclist.clear();
}


void Map::loadmap( string filename )
{
    string tmp;
    FILE *fp = NULL;
    ssize_t rr = 0;
    char *line = NULL;
    size_t len = 0, linenum = 0;
    vector<string> cells;
    NPCNode node;


    clear();
    enforce(( fp = fopen( filename.c_str(), "r" )) != NULL,
            "Failed to open " << filename << " (" << strerror( errno ) << ")" );

    while(( rr = readline( &line, &len, fp )) != -1 ) {
        ++linenum;
        tmp = line;
        trim( tmp );
        if( tmp.empty()) continue;
       
        cells.clear();
        stringSep( tmp, cells, ',' );
        if( !hloaded ) {
            enforce( cells.size() == 4,
                    "Bad Map File: " << filename << "\n" << linenum << ": " << line );
            id = convert( cells[0] );
            name = cells[1];
            width = convert( cells[2] );
            height = convert( cells[3] );
            hloaded = true;
            enforce(  10000 <= id && id <= 11000, "Bad Map ID\n" << linenum << ": " 
                    << line );
        } else if( tilemap.size() < ( width * height )) {
            enforce( cells.size() == width, "Bad Map Line\n" << linenum << ": "
                    << line );
            for( size_t i = 0; i < cells.size(); ++i ) {
                tilemap.push_back( MapTile( cells[i] ));
                //tilemap.back().print();
            }
        } else {
            // read in NPCs
            enforce( cells.size() == 7, "Bad Map Line\n" << linenum << ": "
                    << line );
            node.npc_id = convert( cells[0] );
            node.x = convert( cells[1] );
            node.y = convert( cells[2] );
            node.direction = convert( cells[3] );
            node.alive = convert( cells[4] );
            node.type = convert( cells[5] );
            node.mut_id = convert( cells[6] );
            npclist.push_back( node );
        }
    }
    enforce( tilemap.size() == ( width * height ),
            "Bad Map! Got " << tilemap.size() << " tiles.  Expecting " <<
            width * height << " tiles." << endl );

    cout << "Map " << name << " has " << npclist.size() << " NPCS" << endl;

    enforce( fclose( fp ) == 0,
            "Failed to close " << filename << " (" << strerror( errno ) << ")" );
    free( line );
}


void Map::writemap( FILE *fp )
{
    U32 strlen = name.size();
    U32 npclen = npclist.size();

    enforce( hloaded, "Map Not Loaded!" );
    // write ID
    writeBlock( fp, &id );
    // write width, height, strlen
    writeBlock( fp, &width );
    writeBlock( fp, &height );
    writeBlock( fp, &strlen );
    // write string
    writeString( fp, name );

    // write tiledata
    for( size_t i = 0; i < tilemap.size(); ++i ) {
        writeBlock( fp, &(tilemap[i]));
    }

    // write npclist
    writeBlock( fp, &npclen );
    for( size_t i = 0; i < npclen; ++i ) {
        writeBlock( fp, &(npclist[i]));
    }

}

template <class T>
void Map::writeBlock( FILE *fp, T *block )
{
    enforce( fwrite( block, 1, sizeof( T ), fp ) == sizeof( T ),
            "Failed to write block to file: " << strerror( errno ));
}

void Map::writeString( FILE *fp, string &str )
{
    enforce( fwrite( str.c_str(), 1, str.size(), fp ) == str.size(),
            "Failed to write string to file: " << strerror( errno ));
}

