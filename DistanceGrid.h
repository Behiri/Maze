#pragma once
#include "Grid.h"
#include "Distances.h"
#include <memory>

class DistanceGrid :
	public Grid
{
public:
	DistanceGrid();
	DistanceGrid(int row, int col);

public:
	std::unique_ptr<Distances> distances;
	void CalcDistancesFrom(Cell* root);
public:
	Cell* operator()(int row, int col);
	std::string contents_of(Cell* cell, Cell* dis) const override;
	std::unique_ptr<Distances> path_to(Cell* goal);
private:
	std::unique_ptr<Distances> calcDist(Cell* root);
};
