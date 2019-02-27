#include <iostream>
#include "grid.h"
#include "Cell.h"
#include "BinaryTree.h"
#include "SideWinder.h"
#include "Distances.h"
#include "DistanceGrid.h"
#include "SFML/Graphics.hpp"


int main()
{
	using std::cout;
	using std::endl;

	try
	{
		const int rows = 20;
		const int columns = 30;
		DistanceGrid grid(rows, columns);

		SideWinder sideWinder;
		sideWinder.on(grid);
		//BinaryTree binaryTree;
		//binaryTree.on(grid);

		Cell* start = grid(10, 10);

		//grid.path_toDistance(grid(15, 20));
		grid.to_s(start);
		//cout << grid << endl;

		grid.to_png(16);
	}
	catch (const std::exception& ex)
	{
		std::cerr << typeid(ex).name() << " caught in main: " << ex.what() << std::endl;
		return 1;
	}
	
}