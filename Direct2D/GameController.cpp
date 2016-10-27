#include "GameController.h"

bool GameController::loading;
GameLevel* GameController::currentLevel;
HPTimer* GameController::time;


void GameController::init()
{
	loading = true;
	currentLevel = nullptr;
	time = new HPTimer();
}

void GameController::loadInitialLevel(GameLevel* level)
{
	loading = true;
	currentLevel = level;
	currentLevel->load();
	loading = false;
}

void GameController::switchLevel(GameLevel* level)
{
	loading = true;
	currentLevel->unload();
	level->load();
	delete currentLevel;
	currentLevel = level;
	loading = false;
}

void GameController::update()
{
	if (loading) return;
	time->update();
	currentLevel->update(time->getTimeTotal(), time->getTimeDelta());
}

void GameController::render()
{
	if (loading) return;
	currentLevel->render();
}