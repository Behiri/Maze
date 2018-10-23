#include "Distances.h"

Distances::Distances(Cell* cell)
	: root(cell)
{
	cells[root] = 0;
}


Distances::~Distances()
{
}

void Distances::setDistance(Cell* cell, int dist)
{
	cells[cell] = dist;
}

const int Distances::operator[](Cell* cell)
{
	if (cells.count(cell) == 0)
		return -1;

	return cells[cell];
}

std::map<Cell*, int> Distances::getCells()
{
	return cells;
}
