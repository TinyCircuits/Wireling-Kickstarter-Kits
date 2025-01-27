/*
GraphicsBuffer.h - Last modified 6 January 2020

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Written by Ben Rose for TinyCircuits.

The latest version of this library can be found at https://TinyCircuits.com/
*/

#include "Arduino.h"

#ifndef GraphicsBuffer_h
#define GraphicsBuffer_h

#define colorDepth8BPP 8
#define colorDepth16BPP 16
#define colorDepth1BPP 1

#ifndef TinyScreen_h
//'TinyScreen_h' is currently the best way to check if font data is already defined/included
typedef struct
{
	const uint8_t width;
	const uint16_t offset;
	
} FONT_CHAR_INFO;	

typedef struct
{
	const unsigned char height;
	const char startCh;
	const char endCh;
	const FONT_CHAR_INFO*	charDesc;
	const unsigned char* bitmap;
		
} FONT_INFO;
#include "font.h"

#endif

class GraphicsBuffer : public Print {
  public:
    const uint16_t width;
    const uint16_t height;
    const uint8_t bitsPerPixel;
    GraphicsBuffer(const uint16_t widthInit, const uint16_t heightInit, const uint8_t bitsPerPixelInit):
      width(widthInit), height(heightInit), bitsPerPixel(bitsPerPixelInit) {
        _xMax = width-1;
        _yMax = height-1;
        _bitDepth=bitsPerPixel;
      };
    int begin(void);
    //basic graphics commands
    void writePixel(uint16_t);
    void incrementPixel(void);
    void setX(uint8_t, uint8_t);
    void setY(uint8_t, uint8_t);
    void goTo(uint8_t x, uint8_t y);
    void drawPixel(uint8_t, uint8_t, uint16_t);
    void clear();
    //font
    void setFont(const FONT_INFO&);
    uint8_t getFontHeight(const FONT_INFO&);
    uint8_t getFontHeight(void);
    uint8_t getPrintWidth(char *);
    void setCursor(int, int);
    void fontColor(uint16_t, uint16_t);
    virtual size_t write(uint8_t);
    uint8_t* getBuffer();
    uint16_t getBufferSize();

  private:
    uint8_t *bufferData;
    uint16_t  _bufferSize;
    int _cursorX, _cursorY;
    uint8_t _xMax, _yMax, _pixelXinc, _pixelYinc, _cursorXmin, _cursorYmin, _cursorXmax, _cursorYmax;
    uint8_t _fontHeight, _fontFirstCh, _fontLastCh, _bitDepth, _colorMode;
    uint16_t  _fontColor, _fontBGcolor;
    const FONT_CHAR_INFO* _fontDescriptor;
    const unsigned char* _fontBitmap;
};

#endif