#pragma once
#include "grid.h"

class BinaryTree
{
public:

	void on(Grid& g)
	{
		g.each_cell([](Cell& cell) {
			bool headOrTail = std::rand() % 2; // 0 : head == curve south

			bool at_eastern_boundary = (cell.pEast == nullptr);
			bool at_southern_boundary = (cell.pSouth == nullptr);

			if (at_eastern_boundary)
			{
				if (cell.pSouth)
					cell.link(cell.pSouth);
			}
			else if (at_southern_boundary)
			{
				if (cell.pEast)
					cell.link(cell.pEast);
			}
			else
			{
				headOrTail ? cell.link(cell.pSouth) : cell.link(cell.pEast);
			}
		});
	}

	void on2(Grid& g)
	{
		int ROWS = g.rows;
		int COLUMNS = g.columns;

		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLUMNS; j++) {

				bool leftOrDown = std::rand() % 2;
				Cell *m = g.grid[i][j];

				if (i == ROWS - 1 && j == COLUMNS - 1)
					continue;

				if (j == COLUMNS - 1 && i != ROWS)
				{
					m->link(g.grid[i + 1][j], true);
					//std::cout << "first: " << "i: " << i << " j: " << j << std::endl;
					continue;
				}

				if (i == ROWS - 1 && j != COLUMNS)
				{
					m->link(g.grid[i][j + 1], true);
					//std::cout << "second: " << "i: " << i << " j: " << j << std::endl;
					continue;
				}


				if (leftOrDown == 0)
				{
					m->link(g.grid[i + 1][j], true);
				}
				else
				{
					m->link(g.grid[i][j + 1], true);
				}
			}
	}

	void on3(Grid& inGrid)
	{
		for (auto& row : inGrid.grid)
		{
			for (auto& cell : row) {

				bool headOrTail = std::rand() % 2; // 0 : head == curve south

				bool at_eastern_boundary = (cell->pEast == nullptr);
				bool at_southern_boundary = (cell->pSouth == nullptr);

				if (at_eastern_boundary)
				{
					if (cell->pSouth)
						cell->link(cell->pSouth);
				}
				else if(at_southern_boundary)
				{
					if (cell->pEast)
						cell->link(cell->pEast);
				}
				else 
				{
					headOrTail ? cell->link(cell->pSouth) : cell->link(cell->pEast);
				}
				

			}

		}
	}
};