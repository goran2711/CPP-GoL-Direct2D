#pragma once
#include <wincodec.h>
#include "Graphics.h"

class SpriteSheet
{
	Graphics* graphics;
	ID2D1Bitmap* bmp;
	int spriteWidth, spriteHeight;
	int spritesAcross;

public:
	SpriteSheet(wchar_t* filename, Graphics* graphics_);
	SpriteSheet(wchar_t* filename, Graphics* graphics_, int spriteWidth, int spriteHeight);
	~SpriteSheet();

	void draw();
	void draw(int index, float x, float y);
};

