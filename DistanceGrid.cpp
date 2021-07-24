#include "DistanceGrid.h"
#include <string>
#include <ctime>
#include "helper.h"

DistanceGrid::DistanceGrid()
{
}

DistanceGrid::DistanceGrid(int row, int col)
	: Grid(row, col)
{
}

void DistanceGrid::CalcDistancesFrom(Cell* root)
{
	distances = std::move(calcDist(root));
}

Cell* DistanceGrid::operator()(int row, int col)
{
	return Grid::operator()(row, col);
}

std::string DistanceGrid::contents_of(Cell* cell = nullptr, Cell* dis = nullptr) const
{
	std::string out{};
	if ((distances->cellDistances).count(cell) != 1) return "   ";
	int s = distances->cellDistances.at(cell);
	int offset = GetNumberOfDigits(s);
	if (offset == 1) // if we have 1 digit just print it in center of cell
	{
		out.append(" ");
		out.append(std::to_string(s));
		out.append(" ");
	}
	else if (offset > 3) // if we have more than 3 digits it can't fit cell
	{
		out.append(" ? ");
	}
	else
	{
		out.append(3 - offset, ' ');
		out.append(std::to_string(s));
	}
	return out;
}

std::unique_ptr<Distances> DistanceGrid::calcDist(Cell* root)
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
			for (auto& [adj, linked] : cell->links)
			{
				if (dist->cellDistances[adj] != NULL || adj == root)
					continue;
				dist->setDistance(adj, dist->cellDistances[cell] + 1);
				new_frontier.push_back(adj);
			}
		}
		frontier = new_frontier;
	}
	return dist;
}

std::unique_ptr<Distances> DistanceGrid::path_to(Cell* goal)
{
	Cell* current = goal;
	//! path renamed from breadcrumbs
	auto path = std::make_unique<Distances>(root);
	path->cellDistances[current] = distances->cellDistances[current];

	while (current != root)
	{
		for (auto& [neighbor, linked] : current->links)
		{
			if (distances->cellDistances[neighbor] < distances->cellDistances[current] && linked)
			{
				path->cellDistances[neighbor] = distances->cellDistances[neighbor];
				current = neighbor;
				break;
			}
		}
	}

	distances = std::move(path);
	return path;
}
