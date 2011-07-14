

#include "mod_resource.h"




void ModResource::ReadString( FILE *fp, string &filename, string &str, U32 strlen )
{
    char *line = NULL;
    enforce(( line = new char[strlen+1] ) != NULL, "malloc: " << strerror( errno ));
    enforce( fread( line, 1, strlen , fp ) == strlen,
            "Failed to write block to " << filename << " [ " << 
            strerror( errno ) );
    line[strlen] = 0;
    str = line;
    delete[] line;
}

void ModResource::WriteString( FILE *fp, string &filename, string &str )
{
    enforce( fwrite( str.c_str(), 1, str.size() , fp ) == str.size(),
            "Failed to write block to " << filename << " [ " << 
            strerror( errno ) );
}

