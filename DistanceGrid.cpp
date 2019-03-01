#include "DistanceGrid.h"
#include <string>
#include <ctime>
#include <memory>
#include "helper.h"

DistanceGrid::DistanceGrid()
{
}

DistanceGrid::DistanceGrid(int row, int col)
	: Grid(row, col)
{
}

void DistanceGrid::initDistances(Cell* root)
{
	distances = calcDist(root);
}

Cell* DistanceGrid::operator()(int row, int col)
{
	return Grid::operator()(row, col);
}

std::string DistanceGrid::contents_of(Cell* cell = nullptr, Cell* dis = nullptr) const
{
	std::string out{};
	if ((distances->cells).count(cell) == 1) return "   ";
	int s = distances->cells.at(cell);
	int offset = GetNumberOfDigits(s);
	out.append(3 - offset, ' ');
	out.append(std::to_string(s));
	return out;
}

std::unique_ptr<Distances> DistanceGrid::calcDist(Cell * root)
{
	auto dist = std::make_unique<Distances>(root);

	std::vector<Cell*> frontier;
	frontier.push_back(root);
	dist->setDistance(root, 0);

			while (frontier.size() != 0)
			{
				// when frontier ends this will be new frontier
				std::vector<Cell*> new_frontier; 

				for (auto cell : frontier)
				{
					for (auto [adj, linked] : cell->links)
					{
						if (dist->cells[adj] != NULL || adj == root) 
							continue;
						dist->setDistance(adj, dist->cells[cell] + 1);
						new_frontier.push_back(adj);
					}
				}
				frontier = new_frontier;
		
	}
	return dist;
}

DistanceGrid::~DistanceGrid()
{
}