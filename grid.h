#pragma once
#include <vector>
#include <functional>
#include "Distances.h"
#include "Cell.h"
#include "SFML/Graphics.hpp"

class Grid
{
public:
	Grid();
	Grid(int rows, int columns);

public:
	int rows, columns;
	std::vector<std::vector<Cell*>> grid; // grid[row][column]
	Cell* root;
	Cell* farthest;
	int maximumDistance;

	void prepare_grid();
	void configure_cells();
	Cell* Random_Cell();
	int size();
	void each_row();
	void each_cell(std::function<void(Cell&)>);
	Cell* operator()(const size_t rowIndex, const size_t columnIndex);
	virtual std::string contents_of(Cell* cell, Cell* dist) const;
	virtual sf::Color Background_color_for(Cell* cell);
	friend std::ostream& operator<< (std::ostream& out, const Grid& inGrid);
	void to_s(Cell* root);
	void to_png(int cellSize);
	void to_png_Animated(int cellSize);
};
