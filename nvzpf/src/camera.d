module  src.camera;


import  src.gameobjects;


class Camera
    : DynamicObject
{

     this( short _x, short _y, short width, short height, int _id )
     {
        super( _x, _y, width, height, _id );
     }
      
     /// center the camera around an object  
     void center( StaticObject obj )
     {
        px = cast(short)(obj.x + (obj.w / 2) - w / 2 );
        py = cast(short)(obj.y + (obj.h / 2) - h / 2 );
     }

     private:

}    
   
