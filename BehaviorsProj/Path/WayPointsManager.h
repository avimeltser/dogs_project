/*
 * WayPointsManager.h
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_
#include <vector>
#include "../Utilities/Global.h"
#include "../Utilities/Position.h"
#include "../ConfigurationManager.h"
#include "../Utilities/Point.h"

class WayPointsManager {
private:
	vector<Position> _wayPoints;
	unsigned _last_Point;
	int _last_Direction;
	// Claculated path
	vector<Point> _path;
public:
	WayPointsManager(RobotParameters& params);
	virtual ~WayPointsManager();
	vector<Position> getWayPoints();
	void addWayPoint(Position waypoint);

	int getNextWayPoint();
	void calculateWayPoints();

	void changeWaypointToImageResolution();

private:
	double _mapRes;
	int _gridRes;
};

#endif /* WAYPOINTSMANAGER_H_ */
