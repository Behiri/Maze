#pragma once
#include "DistanceGrid.h"

class ColoredGrid :
	public DistanceGrid
{
public:
	ColoredGrid(int row, int coloumn);
public:
	sf::Color Background_color_for(Cell* cell) override;
};