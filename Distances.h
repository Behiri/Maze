#pragma once
#include <map>
#include "Cell.h"

class Distances
{
public:
	Distances(Cell* cell);
	~Distances();

	Cell* root; // start point
	void setDistance(Cell* cell, int dist);
	std::map<Cell*, int> cells;
	const int operator[](Cell* cell);
	std::map<Cell*, int> getCells();
};