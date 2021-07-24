#include <iostream>
#include "Grid.h"
#include "Cell.h"
#include "BinaryTree.h"
#include "SideWinder.h"
#include "AldousBroder.h"
#include "Distances.h"
#include "ColoredGrid.h"
#include "SFML/Graphics.hpp"
#include "Wilsons.h"

int main()
{
	using std::cout;
	using std::endl;

	try
	{
		const int rows = 32;
		const int columns = 32;
		//DistanceGrid grid(rows, columns);
		ColoredGrid grid(rows, columns);

		//SideWinder sideWinder;
		//sideWinder.on(grid);
		//BinaryTree binaryTree;
		//binaryTree.on(grid);
		//AldousBroder aldousBroder;
		//aldousBroder.on(grid);
		Wilsons wilsons;
		wilsons.on(grid);

		Cell* start = grid(0, 0);
		Cell* end = grid(rows - 1, columns - 1);

		grid.CalcDistancesFrom(start);
		start = grid.distances->LongestPath(end).first;
		grid.root = start;

		grid.CalcDistancesFrom(start);
		auto temp = grid.distances->LongestPath(start);
		end = temp.first;
		grid.farthest = end;
		grid.maximumDistance = temp.second;

		//grid.path_to(end);
		//grid.to_s(start);
		//grid.CalcDistancesFrom(start);
		grid.to_png(16);
		//grid.to_png_Animated(32);
	}
	catch (const std::exception& ex)
	{
		std::cerr << typeid(ex).name() << " caught in main: " << ex.what() << std::endl;
		return 1;
	}
}