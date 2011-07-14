

#ifndef OZ_FMACS_H
#define OZ_FMACS_H


#define GETSET( TYPE, NAME, DATA ) TYPE NAME() { return DATA; } \
TYPE NAME( TYPE v ) { DATA = v; return DATA; }    


#define REFGETSET( TYPE, NAME, DATA ) TYPE &NAME() { return DATA; } \
TYPE &NAME( TYPE v ) { DATA = v; return DATA; }    


#endif

