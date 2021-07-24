#include "Distances.h"
#include "Cell.h"

Distances::Distances(Cell* cell)
	: root(cell)
{
	cellDistances[root] = 0;
}

Distances::~Distances()
{
}

void Distances::setDistance(Cell* cell, int dist)
{
	cell->distance = dist;
	cellDistances[cell] = dist;
}

const int Distances::operator[](Cell* cell)
{
	if (cellDistances.count(cell) == 0)
		return -1;

	return cellDistances[cell];
}

std::map<Cell*, int> Distances::getCells()
{
	return cellDistances;
}

std::pair<Cell*, int> Distances::LongestPath(Cell* root)
{
	int maxDist = 0;
	Cell* maxCell = root;
	for (auto& [cell, distance] : cellDistances)
	{
		if (distance > maxDist)
		{
			maxDist = distance;
			maxCell = cell;
		}
	}

	return std::make_pair(maxCell, maxDist);
}