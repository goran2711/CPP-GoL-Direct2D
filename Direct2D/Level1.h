#pragma once
#include <vector>
#include <random>
#include "GameLevel.h"

struct Node {
	Node():
		alive(false)
	{}
	Node(D2D1_POINT_2F pos_, bool alive_ = false):
		pos(pos_)
	{	
		if (alive = alive_)
		{
			colour = D2D1::ColorF(0xFF00FF);
		}
		else
		{
			colour = D2D1::ColorF(0x333333);
		}
	}

	void revive()
	{
		if (!alive)
		{
			colour = D2D1::ColorF(0xFF00FF);
			alive = true;
		}
	}

	void die()
	{
		if (alive)
		{
			colour = D2D1::ColorF(0x333333);
			alive = false;
		}
	}

	D2D1_POINT_2F pos;
	D2D1_COLOR_F colour;
	bool alive;
};

class Level1 : public GameLevel
{
	std::default_random_engine* generator;
	std::vector< std::vector<Node> > nodes;
	const int GRID_SIZE;

	double nextFunctionCall;
	const float FUNCTION_CALL_GAP;

public:
	Level1();
	~Level1();

	void load() override;
	void unload() override;
	void update(double totalTime, double deltaTime) override;
	void render() override;
};

