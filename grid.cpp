#include "grid.h"
#include "Cell.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "SFML/Graphics.hpp"


Grid::Grid(int rows, int columns) :
	rows(rows),
	columns(columns)
{
	this->prepare_grid();
	this->configure_cells();
	std::srand((unsigned int)time(0));
	root = grid[0][0];
}

Grid::Grid()
{

}

void Grid::prepare_grid()
{
	int row = rows;
	int col = columns;

	grid.resize(row);
	for (int i = 0; i < row; i++) {
		grid[i].resize(col);
		grid[i] = std::vector<Cell*>(col);
		for (int j = 0; j < col; j++)
		{
			grid[i][j] = new Cell(i, j);

		}
	}
	//std::cout << "Grid prepared!\n";
}

void Grid::configure_cells()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {

			if ((i - 1) >= 0) 
				grid[i][j]->pNorth = grid[i - 1][j];
			else grid[i][j]->pNorth = nullptr;

			if (i + 1 < rows) 
				grid[i][j]->pSouth = grid[i + 1][j];
			else grid[i][j]->pSouth = nullptr;

			if (j + 1 < columns) 
				grid[i][j]->pEast  = grid[i][j + 1];
			else grid[i][j]->pEast = nullptr;

			if (j - 1 >= 0)		
				grid[i][j]->pWest  = grid[i][j - 1]; 
			else grid[i][j]->pWest = nullptr;
		}
	//std::cout << "Grid cells configured!\n";
}

Cell* Grid::Random_Cell()
{
	int row = std::rand() % this->rows;
	int column = std::rand() % grid[row].size();

	return grid[row][column];
}

int Grid::size()
{
	return rows * columns;
}

void Grid::each_row()
{
	
}

void Grid::each_cell(std::function<void(Cell&)> inFunc)
{
	for (auto& row : grid)
		for (auto& cell : row)
			inFunc(*cell);
}

Cell* Grid::operator()(const size_t rowIndex, const size_t columnIndex)
{
	if (rowIndex > rows || columnIndex > columns)
	{
		throw std::out_of_range("Out of bounds index.");
		/*std::cout << "grid(" << rowIndex << "," << columnIndex
			<< ") is out of bounds!" << std::endl;
		return grid[0][0];*/
	}

	return grid[rowIndex][columnIndex];
}


std::string Grid::contents_of(Cell* root = nullptr, Cell* dist = nullptr) const
{
	return "   ";
}

std::ostream & operator<<(std::ostream & out, const Grid & inGrid)
{
	std::string output = "";
	bool top = true;
	for (auto& eachRow : inGrid.grid) {
		output += "+";

		for (auto cell : eachRow)
		{
			if (cell->nRow == 0 || !cell->isLinked(cell->pNorth)) {
				output.append(3, '-');
				output.append("+");
			}
			else
			{
				output.append(3, ' ');
				output.append("+");
			}
		}

		output.append("\n");
		output.append("|");

		for (auto cell : eachRow)
		{
			if (!cell->isLinked(cell->pEast)) {
				output.append(3, ' ');
				output.append("|");
			}
			else
			{
				output.append(3, ' ');
				output.append(" ");
			}
		}

		output.append("\n");

	}

	output.append("+");

	for (int i = 0; i < inGrid.columns; i++)
	{
		output.append(3, '-');
		output.append("+");
	}
	out << output;
	return out;
}

void Grid::to_s(Cell* root)
{
	//std::ostream out;
	std::string output = "";
	bool top = true;
	for (auto& eachRow : grid) {
		output += "+";

		for (auto cell : eachRow)
		{
			if (cell->nRow == 0 || !cell->isLinked(cell->pNorth)) {
				output.append(3, '-');
				output.append("+");
			}
			else
			{
				output.append(3, ' ');
				output.append("+");
			}
		}

		output.append("\n");
		output.append("|");

		for (auto cell : eachRow)
		{
			if (!cell->isLinked(cell->pEast)) {
			
				output.append(contents_of(cell));
				output.append("|");
			}
			else
			{
// 				auto s = root->calcDist(cell);
// 				int offset = GetNumberOfDigits(s);
// 				output.append(3 - offset, ' ');
// 				output.append(std::to_string(s));
				output.append(contents_of(cell));
				output.append(" ");
			}
		}

		output.append("\n");

	}

	output.append("+");

	for (int i = 0; i < columns; i++)
	{
		output.append(3, '-');
		output.append("+");
	}
	//out << output;
	std::cout << output << std::endl;
}

void Grid::to_png(int cellSize = 10)
{
	unsigned int img_width = cellSize * columns;
	unsigned int img_height = cellSize * rows;

	sf::RenderWindow window(sf::VideoMode(img_width + 1, img_height + 1), "Maze");
	sf::RectangleShape line(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize) / 5.f));
	line.setFillColor(sf::Color::Magenta);
	window.setFramerateLimit(60);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		for (int i = 0; i <= columns;i++)
			for (int j = 0; j <= rows; j++)
			{
				line.setSize(sf::Vector2f(cellSize / 5.0, cellSize / 5.0));
				line.setPosition(i * cellSize - cellSize / 5.0, j * cellSize);
				window.draw(line);
			}	
		line.setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize) / 5.f));

		for (auto& n : grid) {
			for (auto cell : n)
			{
				float x1 = static_cast<float>(cell->nColumn * cellSize);
				float y1 = static_cast<float>(cell->nRow * cellSize);
				float x2 = static_cast<float>((cell->nColumn + 1) * cellSize);
				float y2 = static_cast<float>((cell->nRow + 1) * cellSize);

				if (cell->pSouth != nullptr && !cell->isLinked(cell->pSouth))
				{
					line.setPosition(x1, y2);
					window.draw(line);
				}
				else if (cell->pSouth == nullptr)
				{
					line.setPosition(x1, y2);
					window.draw(line);
				}

				if (cell->pEast != nullptr && !cell->isLinked(cell->pEast))
				{
					line.setPosition(x2, y1);
					line.setRotation(90.f);
					window.draw(line);
					line.setRotation(0.f);
				}
				else if (cell->pEast == nullptr)
				{
					line.setPosition(x2, y1);
					line.setRotation(90.f);
					window.draw(line);
					line.setRotation(0.f);
				}
				if (cell->pNorth != nullptr && !cell->isLinked(cell->pNorth))
				{
					line.setPosition(x1, y1);
					window.draw(line);
				}
				else if (cell->pNorth == nullptr)
				{
					line.setPosition(x1, y1);
					window.draw(line);
				}

				if (cell->pWest != nullptr && !cell->isLinked(cell->pWest))
				{
					line.setPosition(x1, y1);
					line.setRotation(90.f);
					window.draw(line);

					line.setRotation(0.f);
				}
				else if (cell->pWest == nullptr)
				{
					line.setPosition(x1 + 3, y1);
					line.setRotation(90.f);
					window.draw(line);
					line.setRotation(0.f);
				}
			}
		}
		window.display();
	}
	//return EXIT_SUCCESS;
}
