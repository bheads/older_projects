

#ifndef OZ_IMAGE_MANGER_H
#define OZ_IMAGE_MANGER_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include <string>
#include <map>
using namespace std;

#include "error.h"
#include "stdtype.h"
#include "pack.h"


class ImageManager
{
    public:
        ImageManager( PackManager &p )
            : packman( p ), images()
        {}

        ~ImageManager()
        {
            images.clear();
        }

        Image &get( U32 ); 

    private:
        PackManager &packman;
        map<U32, Image> images;
};

#endif

