#include <iostream>
#include "cell.h"

Cell::Cell(int row, int column)
	: nRow (row)
	, nColumn (column)
{
}

bool Cell::operator<(const Cell & obj) const
{
	if (obj.nRow < this->nRow)
		return false;
	else if (obj.nColumn < this->nColumn)
		return false;
	else return true;
}

void Cell::link(Cell* cell, bool bidi /*= true*/)
{
	//links.insert(std::make_pair(cell, true));
	links[cell] = true;
	if (bidi && cell) cell->link(this, false);
	//return cell;
}

void Cell::unlink(Cell* cell, bool bidi)
{
	links.erase(cell);
	//return cell;
}

std::ostream & operator<<(std::ostream & stream, Cell & cell)
{
	stream << "the cell nRow: " << cell.nRow << " nColumn: " << cell.nColumn << std::endl;
	return stream;
}

bool Cell::isLinked(Cell* cell)
{
	if (cell == nullptr)
	{
		return false;
		std::cout << "Out Of Bounds Check! this cell Row: " << this->nRow 
			<< " Column: " << this->nColumn << std::endl;
	}
	//if (links.find(cell) != links.end())
	if (links.count(cell))
		return true; // found
	else
		return false; // not found
}

