/*
 * PathSearcher.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#include "PathSearcher.h"

PathSearcher::PathSearcher(Grid grid)
: _grid(grid)
{
}

PathSearcher::~PathSearcher() {
	// TODO Auto-generated destructor stub
}

int** PathSearcher::createPowerGrid() {
	int** powerGrid = new int*[this->_grid.getRows()];
	// init power grid
	for (int i = 0; i < this->_grid.getRows(); i++) {
		powerGrid[i] = new int[this->_grid.getCols()];
	}
	// insert values to grid
	// Run over the grid
	for (int nrow = 0; nrow < this->_grid.getRows(); nrow++) {
		for (int ncol = 0; ncol < this->_grid.getCols(); ncol++) {
			powerGrid[nrow][ncol] = 1;

			// run over neighbors of 2*2
			for (int nrow2 = nrow - 2; nrow2 <= nrow + 2; nrow2++) {
				//check if the nrow2 is ok
				if (nrow2 >= 0 && nrow2 < this->_grid.getRows()) {
					//run over the cols
					for (int ncol2 = ncol - 2; ncol2 <= ncol + 2; ncol2++) {
						//check if the cols legel
						if (ncol2 >= 0 && ncol2 < this->_grid.getCols()) {
							// check if a neighbor is a block
							if (this->_grid.getCellValue(nrow2, ncol2) == BLOCK) {
								powerGrid[nrow][ncol] = ALMOST_NEAR_WALL;
								break;
							}
						}
					}
				}
			}

			// run over neighbors of 1*1
			for (int nrow1 = nrow - 1; nrow1 <= nrow + 1; nrow1++) {
				//check if the nrow2 is ok
				if (nrow1 >= 0 && nrow1 < this->_grid.getRows()) {
					//run over the cols
					for (int ncol1 = ncol - 1; ncol1 <= ncol + 1; ncol1++) {
						//check if the cols legel
						if (ncol1 >= 0 && ncol1 < this->_grid.getCols()) {
							// check if a neighbor is a block
							if (this->_grid.getCellValue(nrow1, ncol1) == BLOCK) {
								powerGrid[nrow][ncol] = NEAR_WALL;
								break;
							}
						}
					}
				}
			}
		}
	}

	return powerGrid;
}

// A* implementation
vector<Point> PathSearcher::searchPath(Point startPoint, Point goalPoint) {

	int** powerGrid = createPowerGrid();

	// The set of tentative nodes to be evaluated, initially containing the start node
	vector<Point> open_set;
	open_set.push_back(startPoint);

	// The set of nodes already evaluated.
	vector<Point> closed_set;

	// The map of navigated nodes.
	Point* came_from[this->_grid.getRows()];

	// Init the navigated nodes
	for (int i = 0; i < this->_grid.getRows(); i++) {
		came_from[i] = new Point[this->_grid.getCols()];
	}

	// Insert the startPoint
	came_from[(int) startPoint.getRow()][(int) startPoint.getCol()] =
			startPoint;

	// Cost from start along best known path.
	//g_score(n) is the known cost of getting from the initial node(start) to n
	double* g_score[this->_grid.getRows()];

	// Init g score
	for (int i = 0; i < this->_grid.getRows(); i++) {
		g_score[i] = new double[this->_grid.getCols()];
	}

	// Sets the g score of start point
	g_score[startPoint.getRow()][startPoint.getCol()] = 0;

	// Estimated total cost from start to goal through y.
	//f_score(n) is sum of the known cost + heuristic cost of getting from the initial node(start) to n
	double* f_score[this->_grid.getRows()];

	// Init f score
	for (int i = 0; i < this->_grid.getRows(); i++) {
		f_score[i] = new double[this->_grid.getCols()];
	}

	// Sets the f score of start point
	f_score[startPoint.getRow()][startPoint.getCol()] =
			g_score[startPoint.getRow()][startPoint.getCol()]
					+ heuristicCostEstimate(startPoint, goalPoint);

	// Creating the path holder
	vector<Point> path;

	// Run until not more tentative nodes to be evaluated
	while (open_set.empty() == false) {
		// Get the index of the node in open_set having the lowest f_score[] value
		int lowestValueIndex = getLowestValueFrom(open_set, f_score);
		Point currentPoint = open_set[lowestValueIndex];

		// Check if the current point is the goal point
		if (currentPoint.isEqual(goalPoint)) {
			path = reconstructPath(came_from, goalPoint);
			break;
		}

		// Pop out the node that has the lowest score
		open_set.erase(open_set.begin() + lowestValueIndex);

		// Add the current point to the end of the vector
		closed_set.push_back(currentPoint);

		// Get neighbors of point
		queue<Point> neighborsQueue = getPointNeighbors(currentPoint);

		// Run over neighbors
		while (neighborsQueue.empty() == false) {
			// Get the first neighbor point and pop it out
			Point neighborPoint = neighborsQueue.front();
			neighborsQueue.pop();

			// Check if the neighbor point is in the close_set
			if (isPointInsideVector(closed_set, neighborPoint) == false) {
				// Calc the tentative g score by add the distance between them (1)
				double temp_g_score =
						g_score[currentPoint.getRow()][currentPoint.getCol()]
								+ powerGrid[neighborPoint.getRow()][neighborPoint.getCol()];
				//+ 1;
				/*
				 // if there are blocks around, add their scale to the temp_g_score
				 if (checkObstacleAround(
				 Point(currentPoint.getRow(), currentPoint.getCol()))) {
				 temp_g_score += SCALE_OF_OBSTACLE;
				 }*/

				// Check 1. if we didnt reach this point
				//       2. if we already got to this point from another path and the current path is lower
				if (isPointInsideVector(open_set, neighborPoint) == false
						|| (temp_g_score
								< g_score[neighborPoint.getRow()][neighborPoint.getCol()])) {

					came_from[neighborPoint.getRow()][neighborPoint.getCol()] =
							currentPoint;

					g_score[neighborPoint.getRow()][neighborPoint.getCol()] =
							temp_g_score;

					f_score[neighborPoint.getRow()][neighborPoint.getCol()] =
							temp_g_score
									+ heuristicCostEstimate(neighborPoint,
											goalPoint);

					if (isPointInsideVector(open_set, neighborPoint) == false) {
						open_set.push_back(neighborPoint);
					}
				}
			}
		}
	}

	return path;

}

// Calc the geometric distance between two points
double PathSearcher::heuristicCostEstimate(Point point1, Point point2) {
	double deltaY = point1.getRow() - point2.getRow();
	double deltaX = point1.getCol() - point2.getCol();

	return (sqrt(pow(deltaX, 2.0) + pow(deltaY, 2.0)));
}

// Return the index of the node in vector having the lowest score[] value
int PathSearcher::getLowestValueFrom(vector<Point> vector, double** scores) {
	int bestIndex = 0;
	Point lowest = vector[bestIndex];

	// Run over the vector of nodes
	for (int index = 1; index < vector.size(); index++) {
		Point temp = vector[index];
		if (scores[lowest.getRow()][lowest.getCol()]
				> scores[temp.getRow()][temp.getCol()]) {
			lowest = temp;
			bestIndex = index;
		}
	}

	return bestIndex;
}

vector<Point> PathSearcher::reconstructPath(Point** came_from,
		Point goalPoint) {
	vector<Point> path;
	vector<Point> fixedPath;

	Point current = goalPoint;
	Point pCamefrom = came_from[current.getRow()][current.getCol()];

	// Push the goal point to the path
	path.push_back(current);

	// Run until we reached the start
	while (!current.isEqual(pCamefrom)) {
		path.push_back(pCamefrom);
		current = pCamefrom;
		pCamefrom = came_from[current.getRow()][current.getCol()];
	}

	// Reverse the path
	for (int i = path.size() - 1; i >= 0; i--) {
		fixedPath.push_back(path[i]);
	}

	return fixedPath;
}

// Check point's neighbors
queue<Point> PathSearcher::getPointNeighbors(Point point) {
	queue<Point> q_neighbors;
	int row = point.getRow();
	int col = point.getCol();

	for (int cur_row = row - 1; cur_row <= row + 1; cur_row++) {
		for (int cur_col = col - 1; cur_col <= col + 1; cur_col++) {
			if ((cur_row > 0) && (cur_row < this->_grid.getRows())
					&& (cur_col > 0) && (cur_col < this->_grid.getCols())
					&& !((cur_row == row) && (cur_col == col))) {
				if (this->_grid.getCellValue(cur_row, cur_col) == FREE) {
					q_neighbors.push(Point(cur_row, cur_col));
				}
			}
		}
	}

	return q_neighbors;
}

bool PathSearcher::isPointInsideVector(vector<Point> vector, Point point) {
	// Run over the vector points
	for (unsigned int index = 0; index < vector.size(); index++) {
		// Check if the current point is equal to the given point
		if (vector[index].isEqual(point)) {
			return true;
		}
	}

	return false;
}

Position PathSearcher::calcualteRealPosition(Point point) {
	double gridResolution = this->_grid.getGridResolution();

	double y = point.getRow() / gridResolution + 100 * gridResolution / 2;
	double x = point.getCol() / gridResolution + 100 * gridResolution / 2;

	return Position(x, y, 0);
}

