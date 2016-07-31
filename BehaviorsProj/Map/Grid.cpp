/*
 * Grid.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: colman
 */

#include "Grid.h"

Grid::Grid() {
	// TODO Auto-generated constructor stub

}

Grid::Grid(int rows, int cols, double resolution, unsigned height,
		unsigned width, Position start, Point goal) {
	this->_height = height;
	this->_width = width;
	this->_gridRows = rows;
	this->_gridCols = cols;
	this->_gridResolution = resolution;

	this->_startPosition = Position(start.getRow(), start.getCol(), start.getYaw());
	this->_startPoint = Point(start.getRow(), start.getCol());
	this->_goalPoint = Point(goal.getRow(), goal.getCol());

	this->_grid = new int*[rows];

	for(int row = 0; row < rows; row++)
	{
		this->_grid[row] = new int[cols];
	}

	for (int row = 0; row < this->_gridRows; row++) {
		for (int col = 0; col < this->_gridCols; col++) {
			_grid[row][col] = FREE;
		}
	}
}
int Grid::getRows() {
	return this->_gridRows;
}

int Grid::getCols() {
	return this->_gridCols;
}

void Grid::setCellValue(int row, int col, int value) {
	this->_grid[row][col] = value;
}

int Grid::getCellValue(int row, int col) {
	return this->_grid[row][col];
}

Point Grid::getStartPoint() {
	return this->_startPoint;
}

Point Grid::getGoalPoint() {
	return this->_goalPoint;
}

double Grid::getGridResolution() {
	return this->_gridResolution;
}

void Grid::initGridByMatrix(int** grid) {
	//init _grid by given grid
	for (int row = 0; row < this->_gridRows; row++) {
		for (int col = 0; col < this->_gridCols; col++) {
			setCellValue(row, col, grid[row][col]);
		}
	}
}

Grid::~Grid() {
	// TODO Auto-generated destructor stub
}

