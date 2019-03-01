#pragma once
#include <map>

class Cell;

class Distances
{
public:
	Distances(Cell* cell = nullptr);
	~Distances();

	Cell* root; // start point
	void setDistance(Cell* cell, int dist);
	std::map<Cell*, int> cells;
	const int operator[](Cell* cell);
	std::map<Cell*, int> getCells();
};