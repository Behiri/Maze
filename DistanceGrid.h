#pragma once
#include "grid.h"
class DistanceGrid :
	public Grid
{
public:
	DistanceGrid();
	DistanceGrid(int row, int col);
	Cell* operator()(int row, int col);
	//std::string contents_of(Cell* cell, Cell* dist) override;
	std::string contents_of(Cell* cell, Cell* dis) const override;
	~DistanceGrid();
};

