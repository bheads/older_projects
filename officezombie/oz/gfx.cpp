/**************************************
*
* gfx.cpp
* wrapper for drawing basic primitives
* with sfml. strings, lines, polygons, circles.
*
* Nicholas Handran 3/19/2011
*
**************************************/

#include "gfx.h"
#include <iostream>

GFX::GFX(RenderWindow &win, PackManager &p)
:currFont(), fontSize( 20 ), thickness( 1 ), color(255,255,255,255), outlineColor(0,0,0,255), outline ( 0 ), _win(win), Text( ), packman( p ), xy()
{
//currFont.LoadFrom("arial.ttf");
}

GFX::~GFX()
{
}

//Draw string with predefined values return index into vector
void GFX::drawString(U32 x, U32 y, const string &txt)
	{
	Text.SetText(txt);
	Text.SetSize(fontSize);
	Text.SetFont(currFont);
	Text.SetPosition(x, y);
	_win.Draw(Text);
	}

//Draw a string with specified font and size. Load font from memory
void GFX::drawString(U32 x, U32 y, const string &txt, sf::Font fon, F32 size)
	{
		
	}

void GFX::drawString(U32 x, U32 y, const string &txt, F32 size)
	{
	Text.SetText(txt);
	Text.SetSize(size);
	Text.SetFont(currFont);
	Text.SetPosition(x, y);
	_win.Draw(Text);
    }

void GFX::drawString(U32 x, U32 y, const string &txt, F32 size, U8 r, U8 g, U8 b, U8 a )
{
	Text.SetText(txt);
	Text.SetSize(size);
	Text.SetFont(currFont);
	Text.SetPosition(x, y);
    Text.SetColor( Color( r, g, b, a ));
	_win.Draw(Text);
}

void GFX::drawStringCenteredX(U32 y, const string &txt, F32 size, U8 r, U8 g, U8 b, U8 a )
{
	Text.SetText(txt);
	Text.SetSize(size);
	Text.SetFont(currFont);
	Text.SetPosition(0, 0);
    Text.SetColor( Color( r, g, b, a ));
    // find the x
    F32 x = Text.GetCharacterPos( txt.size()).x / 2.0f;
    F32 wx = _win.GetWidth() / 2.0f;
	Text.SetPosition( wx - x, y );
	_win.Draw(Text);
}

//Load a font from a file
void GFX::setFont(string &fon)
	{
	currFont.LoadFromFile(fon);
	}

//Load a font from memory
void GFX::setFont(U32 hash)
	{
	U32 size;
	U8 *data = packman.getNEWdata( hash, size );
	currFont.LoadFromMemory( (char *)data, size);
	delete[] data;
	}

void GFX::setFontSize(F32 size)
	{
	fontSize = size;
	}

void GFX::drawLine(F32 x, F32 y, F32 x2, F32 y2)
	{
	if(line.GetNbPoints() == 0)
		line = sf::Shape::Line(x, y, x2, y2, thickness, color, 0, outlineColor);
	line.SetPointPosition(2, x, y);
	line.SetPointPosition(3, x2, y2);
	_win.Draw(line);
	}

void GFX::drawRect(F32 x, F32 y, F32 x2, F32 y2)
	{
	if(rect.GetNbPoints() == 0)
		rect  = sf::Shape::Rectangle(x, y, x2, y2, color, 1, outlineColor);
	rect.SetColor(color);
	rect.SetPointPosition(0, x, y);
	rect.SetPointPosition(1, x2, y);
	rect.SetPointPosition(2, x2, y2);
	rect.SetPointPosition(3, x, y2);
	_win.Draw(rect);
	}



void GFX::drawRect(F32 x, F32 y, F32 x2, F32 y2, U8 r, U8 b, U8 g)
	{
	if(rect.GetNbPoints() == 0)
		rect  = sf::Shape::Rectangle(x, y, x2, y2, sf::Color(r, b, g), 1, outlineColor);
	rect.SetColor(sf::Color(r, b, g));
	rect.SetPointPosition(0, x, y);
	rect.SetPointPosition(1, x2, y);
	rect.SetPointPosition(2, x2, y2);
	rect.SetPointPosition(3, x, y2);
	_win.Draw(rect);
	}
/*void GFX::setColor(U8 r, U8 b, U8, g)
	{
	color.
	}
*/
/*void GFX::drawShapes()
	{
	for(int i = 0; i<shape.size();i++)
		{
		_win.Draw(shape.at(i);
		}
	}*/
