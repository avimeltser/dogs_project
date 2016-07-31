/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Plans/PlnObstacleAvoid.h"
#include "Robot.h"
#include "Utilities/Position.h"
#include "Utilities/Global.h"
#include "Utilities/Point.h"
#include "LocalizationManager.h"
#include "Particle.h"
#include <vector>
#include <math.h>

class Manager {
	Robot* _robot;
	vector<Position> _waypoints;
	LocalizationManager * _localizationManager;
public:
	Manager(Robot* robot, vector<Position> waypoints, LocalizationManager * locManager);
	void runOnPlayer();
	void runOnRobot();
	virtual ~Manager();
	void readOnRobot();
	void changeYawRobot(double dYaw);
	Position getRobotPosition();

private:
	double calcDistance(Position currentPosition, Position nextPosition);
	void changeDirection(Position currentPosition, Position nextPosition, bool isStartPoint);
	double calcAngleDelta(Position currentPosition, Position nextPosition);
	int calcNextMovement(Position currentPosition, Position nextPosition);

};

#endif /* MANAGER_H_ */
