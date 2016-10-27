#include "GameController.h"
#include "Level1.h"


Level1::Level1():
	GRID_SIZE(10),
	FUNCTION_CALL_GAP(0.1)
{
}


Level1::~Level1()
{
}

void Level1::load()
{
	srand(time(NULL));	// Seed PRNG

	auto renderTarget = graphics->getRenderTarget();
	auto screenSize = renderTarget->GetSize();

	auto nodesPerRow = screenSize.width / GRID_SIZE;
	auto nodesPerColumn = screenSize.height / GRID_SIZE;
	
	nodes.resize(nodesPerRow);

	for (auto& column : nodes)
	{
		column.resize(nodesPerColumn);
	}

	for (int i = 0; i < nodesPerRow; ++i)
	{
		for (int j = 0; j < nodesPerColumn; ++j)
		{
			nodes[i][j] = new Node(D2D1::Point2F(i, j), rand() % 100 < 10);
		}
	}

	nextFunctionCall = FUNCTION_CALL_GAP;
}

void Level1::unload()
{
	for (int i = 0; i < nodes.size(); ++i)
	{
		for (int j = 0; i < nodes[i].size(); ++j)
		{
			delete nodes[i][j];
		}
	}
}

void Level1::update(double totalTime, double deltaTime)
{
	if (totalTime < nextFunctionCall) return;

	int livingNeighbours = 0;
	int currentRow = 0;
	int totalRows = nodes.size();
	int totalColumns = nodes[0].size();
	Node* currentNode;

	auto nodesSnapshot = nodes;

	for (int row = 0; row < totalRows; ++row)
	{
		for (int column = 0; column < totalColumns; ++column)
		{
			livingNeighbours = 0;
			currentNode = nodes[row][column];

			// Check LEFT and RIGHT nodes
			if (column - 1 >= 0)					// LEFT nodes
			{
				if (nodesSnapshot[row][column - 1]->alive)
				{
					++livingNeighbours;
				}
			}
			if (column + 1 < totalColumns)			// RIGHT nodes
			{
				if (nodesSnapshot[row][column + 1]->alive)
				{
					++livingNeighbours;
				}
			}

			// Check ABOVE and BELOW nodes
			if (row - 1 >= 0)						// ABOVE nodes
			{
				for (int i = -1; i <= 1; ++i)		// Check all three ABOVE nodes
				{
					if (column + i < 0 || column + i > totalColumns - 1) continue;	// Skip if out of bounds
					if (nodesSnapshot[row - 1][column + i]->alive)
					{
						++livingNeighbours;
					}
				}
			}
			if (row + 1 < totalRows)				// BELOW nodes
			{
				for (int i = -1; i <= 1; ++i)		// Check all three BELOW nodes
				{
					if (column + i < 0 || column + i > totalColumns - 1) continue;	// Ditto
					if (nodesSnapshot[row + 1][column + i]->alive)
					{
						++livingNeighbours;
					}
				}
			}

			// Check if node survives / dies / is revived
			if (currentNode->alive)
			{
				if (livingNeighbours < 2 || livingNeighbours > 3)
				{
					currentNode->die();
				}
			}
			else
			{
				if (livingNeighbours == 3)
				{
					currentNode->revive();
				}
			}
		}
	}

	nextFunctionCall = totalTime + FUNCTION_CALL_GAP;
}

void Level1::render()
{
	graphics->clearScreen(0.0f, 0.0f, 0.5f);

	for (const auto& nodeColumn : nodes)
	{
		for (const auto& nodeRow : nodeColumn)
		{
			graphics->fillSquare(nodeRow->pos.x, nodeRow->pos.y, GRID_SIZE, nodeRow->colour);
		}
	}

	graphics->drawGrid(GRID_SIZE, D2D1::ColorF(0x0F0F0F));
}