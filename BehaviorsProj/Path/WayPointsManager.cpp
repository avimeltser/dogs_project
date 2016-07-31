/*
 * WayPointsManager.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "WayPointsManager.h"

WayPointsManager::WayPointsManager(RobotParameters& prm) {
	_mapRes = prm.GetMapResolution();
	_gridRes = prm.GetGridResolution();

	this->_last_Point = 0;
	this->_last_Direction = MOVE_FORWARD;
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

	double gridToMapRes = _gridRes/_mapRes;

	// Run over the waypoints and convert them from grid to image resolution
	for(int index=0;index<_wayPoints.size();index++){
		int rowImage = _wayPoints[index].getRow() * gridToMapRes;
		int colImage = _wayPoints[index].getCol() * gridToMapRes;

		_wayPoints[index].setRow(rowImage);
		_wayPoints[index].setCol(colImage);
	}
}

int WayPointsManager::getNextWayPoint() {
	int toReturn;
	this->_last_Point++;

	if (this->_last_Point != this->_path.size()) {
		Point prev = this->_path[this->_last_Point - 1];
		Point next = this->_path[this->_last_Point];

		if (prev.getRow() == next.getRow()) {
			if (prev.getCol() > next.getCol()) {
				toReturn = LEFT;
			} else if (prev.getCol() < next.getCol()) {
				toReturn = RIGHT;
			}
		} else if (prev.getCol() == next.getCol()) {
			if (prev.getRow() > next.getRow()) {
				toReturn = UP;
			} else if (prev.getRow() < next.getRow()) {
				toReturn = DOWN;
			}
		} else {
			if (prev.getRow() > next.getRow()) {
				if (prev.getCol() > next.getCol()) {
					toReturn = UP_LEFT;
				} else {
					toReturn = UP_RIGHT;
				}
			} else {
				if (prev.getCol() > next.getCol()) {
					toReturn = DOWN_LEFT;
				} else {
					toReturn = DOWN_RIGHT;
				}
			}
		}

		if (toReturn == this->_last_Direction) {
			toReturn = MOVE_FORWARD;
		} else {
			this->_last_Direction = toReturn;
		}
	} else {
		toReturn = STOP;
	}

	return toReturn;
}

void WayPointsManager::calculateWayPoints() {
	// get the first direction
	int direction = getNextWayPoint();

	// Run until we stop (get to goal)
	while (direction != STOP) {
		// Check if the movement is not moving forward
		if (direction != MOVE_FORWARD) {
			//TODO: check if we need to enter real position
			//this->_wayPoints.addWayPoint(this->calcualteRealPosition(this->_path[_last_Point -1]));
			this->_wayPoints.push_back(
					Position(this->_path[_last_Point - 1].getRow(),
							this->_path[_last_Point - 1].getCol(), 0));
		}

		direction = getNextWayPoint();
	}

	//this->_wayPoints.addWayPoint(this->calcualteRealPosition(this->_path[_last_Point - 1]));
	this->_wayPoints.push_back(
			Position(this->_path[_last_Point - 1].getRow(),
					this->_path[_last_Point - 1].getCol(), 0));
}


WayPointsManager::~WayPointsManager() {
	// TODO Auto-generated destructor stub
}

