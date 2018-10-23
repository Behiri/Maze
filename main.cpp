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
		const int rows = 15;
		const int columns = 15;
		DistanceGrid grid(rows, columns);

		SideWinder sideWinder;
		sideWinder.on(grid);
		//BinaryTree b;
		//b.on(grid);

		Cell* start = grid(0, 0);

		grid.to_s(start);

		grid.to_png(32);
	}
	catch (const std::exception& ex)
	{
		std::cerr << typeid(ex).name() << " caught in main: " << ex.what() << std::endl;
		return 1;
	}
	
}