#pragma once
#include "Graphics.h"
#include "SpriteSheet.h"

class GameLevel
{
protected:
	static Graphics* graphics;

public:
	static void init(Graphics* graphics_)
	{
		graphics = graphics_;
	}

	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void render() = 0;
	virtual void update(double totalTime, double deltaTime) = 0;
};

