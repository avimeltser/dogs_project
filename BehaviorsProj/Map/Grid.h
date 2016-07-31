/*
 * Grid.h
 *
 *  Created on: Jul 13, 2015
 *      Author: colman
 */

#ifndef GRID_H_
#define GRID_H_
#include "../Utilities/Global.h"
#include "../Utilities/Point.h"
#include "../Utilities/Position.h"

class Grid {

	int** _grid;
	int _gridRows, _gridCols;
	double _gridResolution;
	unsigned _height;
	unsigned _width;

	Position _startPosition;
	Point _startPoint;
	Point _goalPoint;

public:
	Grid();
	Grid(int rows, int cols, double resolution, unsigned height, unsigned width,
			Position _startPosition, Point goal);
	virtual ~Grid();
	void initGridByMatrix(int** grid);
	int getRows();
	int getCols();
	void setCellValue(int row, int col, int value);
	int getCellValue(int row, int col);
	double getGridResolution();
	Point getStartPoint();
	Point getGoalPoint();
};

#endif /* GRID_H_ */
