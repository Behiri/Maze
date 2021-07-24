#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include "MazeGenerator.h"
#include "Grid.h"
#include "helper.h"

class Wilsons : MazeGenerator
{

public:
	void on(Grid& g) override
	{
		std::vector<Cell*> unvisitedCells;
		unvisitedCells.reserve(g.size());
		//std::map<Cell*, bool> IsCellVisitedMap;

		for (size_t i = 0; i < g.rows; i++)
		{
			for (size_t j = 0; j < g.columns; j++)
			{
				Cell* pCell = g(i, j);
				//IsCellVisitedMap[pCell] = false;
				unvisitedCells.push_back(pCell);
			}
		}

		Cell* firstRandomCell = g.Random_Cell();
		/*
		// Another way to remove Items from vector
		const auto newEnd = std::remove(std::begin(unvisitedCells), std::end(unvisitedCells), randomCell);
		unvisitedCells.erase(newEnd, std::end(unvisitedCells));
		*/
		quick_remove_at(unvisitedCells, std::find(std::begin(unvisitedCells),
			std::end(unvisitedCells), firstRandomCell));
		int unvisitedCellsCount = g.size() - 1;
		std::vector<Cell*> path; // maybe stack was better

		while (!unvisitedCells.empty())
		{
			unvisitedCellsCount = std::size(unvisitedCells);
			int randomIndex = std::rand() % unvisitedCellsCount;
			Cell* currentCell = unvisitedCells[randomIndex];
			path.push_back(currentCell);

			while (std::find(std::begin(unvisitedCells), std::end(unvisitedCells), currentCell)
				!= unvisitedCells.end()) // while current cell is not visited
			{
				
				currentCell = currentCell->GetRandomNeighbor();
				path.push_back(currentCell);

				auto it = std::find(std::begin(path), std::end(path) - 1, currentCell);
				if (it != path.end())
				{
					path.erase(it, std::end(path) - 1);
				}
			}


			int pathSize = std::size(path);

			Cell* last = currentCell;
			for (int i = pathSize; i > 0; i--) 
			{
				auto oneToLast = path.back();
				last->link(oneToLast);
				last = oneToLast;
				quick_remove_at(unvisitedCells, std::find(std::begin(unvisitedCells),
					std::end(unvisitedCells), last));
				path.pop_back();
			}
			path.clear();
		}
	}
};