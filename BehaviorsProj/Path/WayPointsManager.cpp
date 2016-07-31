/*
 * WayPointsManager.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "WayPointsManager.h"

WayPointsManager::WayPointsManager() {
	// TODO Auto-generated constructor stub

}


void WayPointsManager::addWayPoint(Position waypoint)
{
	WayPointsManager::_wayPoints.push_back(waypoint);
}

vector<Position> WayPointsManager::getWayPoints()
{
	return this->_wayPoints;
}

void WayPointsManager::changeWaypointToImageResolution()
{
	double mapRes = ConfigurationManager::getMapResolution();
	int gridRes = ConfigurationManager::getGridResolution();

	double gridToMapRes = gridRes/mapRes;

	// Run over the waypoints and convert them from grid to image resolution
	for(int index=0;index<_wayPoints.size();index++){
		int rowImage = _wayPoints[index].getRow() * gridToMapRes;
		int colImage = _wayPoints[index].getCol() * gridToMapRes;

		_wayPoints[index].setRow(rowImage);
		_wayPoints[index].setCol(colImage);
	}
}

WayPointsManager::~WayPointsManager() {
	// TODO Auto-generated destructor stub
}

