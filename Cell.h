#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "Distances.h"

class Cell
{
public:
	Cell(int row = 10, int column = 10);
	//Cell(const Cell &) = delete;
	//Cell& operator= (const Cell&) = delete;

public:
	int nRow, nColumn;
	Cell* pNorth, * pSouth, * pWest, * pEast;
	int distance = -1;

	std::map<Cell*, bool> links;
	bool operator<(const Cell& obj) const;
	std::vector<Cell*> neighbors;

	void link(Cell* cell, bool bidi = true);
	void unlink(Cell* cell, bool bidi = true);
	friend std::ostream& operator<<(std::ostream& stream, Cell& cell);
	bool isLinked(Cell* cell);
	Cell* GetRandomNeighbor();
};
