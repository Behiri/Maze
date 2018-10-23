#pragma once
#include "grid.h"
#include "Cell.h"
#include <vector>
#include <random>

class SideWinder
{
public:
	void on(Grid& inGrid)
	{
		inGrid.each_cell([](Cell& cell) {
			std::vector<Cell*> run;
			run.push_back(&cell);

			bool headOrTail = std::rand() % 2; // 0 : head == curve south

			bool at_eastern_boundary = (cell.pEast == nullptr);
			bool at_southern_boundary = (cell.pSouth == nullptr);

			bool should_close_out = at_eastern_boundary || (!at_southern_boundary && headOrTail == 0);

			if (should_close_out)
			{
				auto member = run[rand() % run.size()];
				if (member->pSouth)
				{
					member->link(member->pSouth);
					run.clear();
				}
			}
			else
			{
				if (cell.pEast)
					cell.link(cell.pEast);
			}
		});
	}

	void on1(Grid& inGrid)
	{
		for(auto& row : inGrid.grid)
		{
			std::vector<Cell*> run;

			for(auto cell : row) {
				run.push_back(cell);

				bool headOrTail = std::rand() % 2; // 0 : head == curve south

				bool at_eastern_boundary = (cell->pEast == nullptr);
				bool at_southern_boundary = (cell->pSouth == nullptr);

				bool should_close_out = at_eastern_boundary || (!at_southern_boundary && headOrTail == 0);

				if (should_close_out)
				{
					Cell* member = run[rand() % run.size()];
					if (member->pSouth)
					{
						member->link(member->pSouth);
						run.clear();
					}
				}
				else
				{
					if (cell->pEast)
						cell->link(cell->pEast);
				}
			}
		}
	}
};