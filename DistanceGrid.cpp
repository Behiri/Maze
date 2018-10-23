#include "DistanceGrid.h"
#include <string>
#include <ctime>
#include "helper.h"

DistanceGrid::DistanceGrid()
{
}

DistanceGrid::DistanceGrid(int row, int col)
	:	Grid(row,col)
{

}

Cell* DistanceGrid::operator()(int row, int col)
{
	return Grid::operator()(row, col);
}

std::string DistanceGrid::contents_of(Cell * cell = nullptr, Cell * dis = nullptr) const
{
	std::string out{};
	auto s = root->calcDist(cell);
	int offset = GetNumberOfDigits(s);
	out.append(3 - offset, ' ');
	out.append(std::to_string(s));
	return out;
}

DistanceGrid::~DistanceGrid()
{
}
