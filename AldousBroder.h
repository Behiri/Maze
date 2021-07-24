#pragma once
#include "MazeGenerator.h"
#include <stdlib.h>
#include "Grid.h"

class AldousBroder : MazeGenerator
{
public:
	void on(Grid& g) override
	{
		int unvisitedCell = g.size() - 1;
		Cell* currencCell = g.Random_Cell();
		Cell* nextCell = nullptr;

		while (unvisitedCell > 0)
		{
			int randomDirection = std::rand() % 4; // 0 : up | 1: right | 2: down | 3: left
			switch (randomDirection)
			{
			case 0: // up 
				nextCell = currencCell->pNorth;
				break;;
			case 1: // right
				nextCell = currencCell->pEast;
				break;;
			case 2: // down
				nextCell = currencCell->pSouth;
				break;;
			case 3: // left
				nextCell = currencCell->pWest;
				break;;
			}

			if(nextCell == nullptr) continue;

			if(!nextCell->links.empty())
			{
				currencCell = nextCell;
			}
			else
			{
				currencCell->link(nextCell);
				currencCell = nextCell;
				unvisitedCell--;
			}

		}

	}

};