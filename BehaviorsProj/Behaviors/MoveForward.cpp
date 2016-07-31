/*
 * MoveForward.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "MoveForward.h"
#define MIN_ANGLE -30
#define MAX_ANGLE 30
#define MAX_DIST_TO_OBSTACLE 0.5
#define FORWARD_SPEED 0.5

MoveForward::MoveForward(Robot *robot) : Behavior(robot) {
	// TODO Auto-generated constructor stub

}

MoveForward::~MoveForward() {
	// TODO Auto-generated destructor stub
}

bool MoveForward::checkObstacleInFront()
{
	bool isObstacleInFront = false;
	int minIndex = _robot->deg_to_index(MIN_ANGLE);
	int maxIndex = _robot->deg_to_index(MAX_ANGLE);

	float *scan = _robot->getLaserScan();

	for (int i = minIndex; i <= maxIndex; i++)
	{
		if (scan[i] < MAX_DIST_TO_OBSTACLE)
		{
			isObstacleInFront = true;
			break;
		}
	}

	return isObstacleInFront;
}


bool MoveForward::startCond()
{
	return !checkObstacleInFront();
}

bool MoveForward::stopCond()
{
	return checkObstacleInFront();
}

void MoveForward::action()
{
	_robot->setSpeed(FORWARD_SPEED, 0);
}
