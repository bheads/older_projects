
#ifndef OZ_ANIMATION_H
#define OZ_ANIMATION_H

#include <string>
#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "error.h"
#include "stdtype.h"
#include "images.h"
#include "mod_resource.h"


// used for saving and loading animation data
struct AnimationNode {
    U32 id;
    F32 frametime;
    U32 framecount;

    void print() {
        cout << "ID: " << id << endl;
        cout << "FT: " << frametime << endl;
        cout << "FC: " << framecount << endl;
    }
};

// holds the basics for an animation
class AnimationData 
    : public ModResource
{
    public:
    
        AnimationData( )
            : ModResource( 0 ), frametime( 0.0f ), frames()
        {}

        void clear();
        void read( FILE *, string & );
        void write( FILE *, string & );

        F32 frametime;
        vector<U32> frames;
};

// A usable animation
class Animation 
{
    public:
        Animation()
            : id( 0 ), framecounter( 0.0f ), frameindex( 0 ), frames(), running( false ),
            loop( false ), sprite()
        {}

        Animation( AnimationData &ad, ImageManager &im )
            : framecounter( 0.0f ), frameindex( 0 ), frames(), 
            running( false ), loop( false ), sprite()
        { set( ad, im ); }


        Animation( const Animation &a )
            : framecounter( a.framecounter ), frameindex( a.frameindex ), frames(), 
            running( a.running ), loop( a.loop ), sprite()
        { }


        ~Animation()
        {
            frames.clear();
        }


        void set( AnimationData &, ImageManager & );

        void runloop() { loop = true; run(); }
        void runonce() { loop = false; run(); }
        void run() { running = true; }
        void stop() { running = false; }
        bool isrunning() { return running; }
        void reset( U32 fi = 0) 
        { frameindex = fi; framecounter = 0.0f; sprite.SetImage( *frames[frameindex] ); }

        void update( F32 );
        void draw( RenderWindow & );
        void position( F32 x, F32 y ) { sprite.SetPosition( x, y ); }
        void move( F32 x, F32 y ) { sprite.Move( x, y ); }
        F32 geth() { return (F32)frames[frameindex]->GetHeight(); }
        F32 getw() { return (F32)frames[frameindex]->GetWidth(); }

        U32 ID() { return id; }

    private:
        U32 id;
        F32 frametime;
        F32 framecounter;
        U32 frameindex;
        vector<Image*> frames;
        bool    running, loop;


    public:
        Sprite  sprite;
};

#endif

