#pragma once
class Grid;

class MazeGenerator
{
public:
	virtual void on(Grid& g) = 0;
};