/***
 * filefunc.h
 *  collection of useful file functions.
 *
 *  Byron Heads bheads@emich.edu
 *
 ***/

#ifndef OZ_FILEFUNC_H
#define OZ_FILEFUNC_H

#include <string>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#include "error.h"

// Test if a file/dir exists
bool FileExists( const string & );
bool GetFileList( vector<string> &, string &, string & );
U32 FileSize( const string );
// since getline is not in the MinGW lib, reimplmented my own
ssize_t readline( char **lineptr, size_t *n, FILE *stream );

void MakeDir( string );
void GetDirList( vector<string> &, string & );

#endif

