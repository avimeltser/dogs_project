/*
 * PathSearcher.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef PATHSEARCHER_H_
#define PATHSEARCHER_H_
#include "../Map/Grid.h"
#include <vector>
#include "../Utilities/Point.h"
#include "../Utilities/Global.h"
#include "../Path/WayPointsManager.h"
#include "../ConfigurationManager.h"
#include "math.h"
#include <queue>

class PathSearcher {
private:
	// data members for navigation
	unsigned _last_Point;
	int _last_Direction;
	WayPointsManager _wayPoints;

	// Grid of the surface
	Grid _grid;

	// Claculated path
	vector<Point> _path;

	int** createPowerGrid();

public:
	PathSearcher(RobotParameters& prm, Grid grid);
	virtual ~PathSearcher();

	vector<Point> searchPath(Point startPoint, Point goalPoint);
	double heuristicCostEstimate(Point point1, Point point2);
	int getLowestValueFrom(vector<Point> vector, double** scores);
	vector<Point> reconstructPath(Point** came_from, Point goalPoint);
	queue<Point> getPointNeighbors(Point point);
	bool isPointInsideVector(vector<Point> vector, Point point);
	int getNextWayPoint();
	void calculateWayPoints();
	Position calcualteRealPosition(Point point);
	vector<Position> getRealPath();
	vector<Position> getWayPoints();



};

#endif /* PATHSEARCHER_H_ */
