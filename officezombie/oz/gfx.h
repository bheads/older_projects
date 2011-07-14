/******************************
*  gfx.h
*  wrapper for drawing basic primitives
*  with SFML. strings, lines, polygons and circles.
*
*  Nicholas Handran 3/15/2011
*
******************************/
#ifndef GFX_H
#define GFX_H

#include <string>
#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "stdtype.h"
//#include "error.h"
#include "pack.h"

class GFX
{

	public:
	GFX(RenderWindow &win, PackManager &p);

	virtual ~GFX();
	//void drawString(U32 x, U32 y, std::string txt,  font);

	//Draw a string with default everythings
	void drawString(U32 x, U32 y, const string &txt);
	
	//Draw a string with specified everything
	void drawString(U32 x, U32 y, const string &txt, sf::Font fon, F32 size);

	//Draw a string with specified everything
	void drawString(U32 x, U32 y, const string &txt, F32 size);
	void drawString(U32 x, U32 y, const string &txt, F32 size, U8 r, U8 g, U8 b, U8 a = 255 );


    // draw centered to string on X
	void drawStringCenteredX(U32 y, const string &txt, F32 size, U8 r, U8 g, U8 b, U8 a = 255 );
	//Draw a line with predefined colors etc
	void drawLine(F32 x, F32 y, F32 x2, F32 y2);

	//Draw a line with specific colors etc
	//void drawLine(F32 x, F32 y, F32 x2, F32
						
	//void drawCircle(U32 x, U32 y, U32 rad);

	void drawRect(F32 x, F32 y, F32 x2, F32 y2);

	void drawRect(F32 x, F32 y, F32 x2, F32 y2, U8 r, U8 b, U8 g);
	//void drawPolygon();

	//load a font from a file
	void setFont(string &fon);
	//load a font from memory
	void setFont(U32 hash);
	//set font size
	void setFontSize(F32 size);

	//void GFX::setDraw(F32 thick, Color col, F32 outl, Color outlcol);
	//protected:
	private:
	sf::Font currFont;
	F32 fontSize;
	F32 thickness;
	Color color;
	Color outlineColor;
	F32 outline;
	RenderWindow &_win;
	sf::String Text;
	PackManager &packman;
	sf::Vector2f xy;
	sf::Shape shape;
	sf::Shape rect;
	sf::Shape line;
};


#endif
