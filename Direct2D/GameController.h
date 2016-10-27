#pragma once
#include "GameLevel.h"
#include "HPTimer.h"

class GameController
{
	// Constructor is private, this is a singleton class. Similar to a namespace
private:
	GameController(); 
	static GameLevel* currentLevel;
	static HPTimer* time;
public:
	static bool loading;

	static void init();

	static void loadInitialLevel(GameLevel* level);
	static void switchLevel(GameLevel* level);
	
	static void update();
	static void render();
};

