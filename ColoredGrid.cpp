#include "ColoredGrid.h"
#include <random>
#include <cassert>

ColoredGrid::ColoredGrid(int rows, int columns)
	: DistanceGrid(rows, columns)
{
}

sf::Color ColoredGrid::Background_color_for(Cell* cell)
{
	//DistanceGrid::CalcDistancesFrom(root);
	Cell* farthestCell = this->farthest;
	int maxDistance = maximumDistance;

	int currentCellDistance = cell->distance;

	float intensity = maxDistance - currentCellDistance;
	intensity /= (float)maxDistance;
	int dark = (255 * intensity);
	int bright = 128 + (127 * intensity);

	int r = bright;
	int g = dark;
	int b = bright;

	bool rgbMode = false;
	if (rgbMode)
	{
		if (intensity >= 0.8)
		{
			r = 255;
			g = 255 - (255 * (1 - intensity) * 5);
			b = 0;
		}
		else if (intensity >= 0.6 && intensity < 0.8)
		{
			r = 255;
			g = 0;
			b = (255 * (0.8 - intensity) * 5);
		}
		else if (intensity >= 0.4 && intensity < 0.6)
		{
			r = 255 - (255 * (0.6 - intensity) * 5);
			g = 0;
			b = 255;
		}
		else if (intensity >= 0.2 && intensity < 0.4)
		{
			r = 0;
			g = (255 * (0.4 - intensity) * 5);
			b = 255;
		}
		else if (intensity >= 0 && intensity < 0.2)
		{
			r = 0;
			g = 255;
			b = 255 - (255 * (0.2 - intensity) * 5);
		}
	}

	assert(g <= 255);
	assert(r <= 255);
	assert(b <= 255);
	assert(g >= 0);
	assert(r >= 0);
	assert(b >= 0);

	return sf::Color(r, g, b);
}