/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, vector<Position> waypoints,
		LocalizationManager * locManager) {
	_robot = robot;
	_waypoints = waypoints;
	_localizationManager = locManager;
}

void Manager::runOnPlayer() {
	unsigned wayPointIndex = 1;

	for (int i = 0; i < 20; i++)
		this->_robot->Read();

	Position nextPosition = this->_waypoints[wayPointIndex];

	// Change the movement direction of the robot
	double angle = this->calcAngleDelta(this->_robot->getPosition(),
			nextPosition);
	this->_robot->ChangeYawRobotPlayer(angle);

	double distance, currentDistance;

	// Run until we didnt reached the last waypoint (goal)
	while (wayPointIndex < this->_waypoints.size()) {
		this->_robot->Read();

		// Calcuate the metric distance between the robot and next position
		distance = this->calcDistance(this->_robot->getPosition(),
				nextPosition);

		if (DEBUG) {
			cout << "Distance between Waypoint (" << nextPosition.getRow()
					<< "," << nextPosition.getCol() << ") to Robot ("
					<< this->_robot->getY() << ", " << this->_robot->getX()
					<< "," << this->_robot->getYaw() << ") is " << distance
					<< endl;
		}
		// Check if the distance of the robot the next waypoint is less than the minimum distance
		if (distance <= MINIMUM_DISTANCE) {

			wayPointIndex++;

			// Check if we reached the last waypoint (goal)
			if (wayPointIndex == this->_waypoints.size()) {
				break;
			}
			nextPosition = this->_waypoints[wayPointIndex];

			// Change the movement direction of the robot
			double angle = this->calcAngleDelta(this->_robot->getPosition(),
					nextPosition);
			this->_robot->ChangeYawRobotPlayer(angle);
		} else {
			this->_robot->setSpeed(FORWARD_SPEED, 0);
		}
	}

	cout << "Goal point reached successfully" << endl;
}

void Manager::runOnRobot() {
	unsigned wayPointIndex = 1;

	/*for (int i = 0; i < 20; i++)
	 this->_robot->Read();*/

	Position nextPosition = this->_waypoints[wayPointIndex];

	// Change the movement direction of the robot
	double angle = this->calcAngleDelta(this->getRobotPosition(), nextPosition);

	this->changeYawRobot(angle);

	this->_robot->setSpeed(FORWARD_SPEED, 0);

	double distance, currentDistance;

	// Run until we didnt reached the last waypoint (goal)
	while (wayPointIndex < this->_waypoints.size()) {
		this->readOnRobot();

		// Calcuate the metric distance between the robot and next position
		distance = this->calcDistance(this->getRobotPosition(), nextPosition);

		if (DEBUG) {
			cout << "Distance between Waypoint (" << nextPosition.getRow()
					<< "," << nextPosition.getCol() << ") to Robot ("
					<< this->getRobotPosition().getRow() << ", "
					<< this->getRobotPosition().getCol() << ","
					<< this->getRobotPosition().getYaw() << ") is " << distance
					<< endl;
		}
		// Check if the distance of the robot the next waypoint is less than the minimum distance
		if (distance <= MINIMUM_DISTANCE) {
			// Get the next waypoint
			wayPointIndex++;

			// Check if we reached the last waypoint (goal)
			if (wayPointIndex == this->_waypoints.size()) {
				break;
			}
			nextPosition = this->_waypoints[wayPointIndex];

			// Change the movement direction of the robot
			double angle = this->calcAngleDelta(this->getRobotPosition(),
					nextPosition);

			this->changeYawRobot(angle);

			this->_robot->setSpeed(FORWARD_SPEED, 0);
		} else {
		}
	}

	cout << "Goal point reached successfully" << endl;
}
void Manager::changeYawRobot(double dYaw) {
	this->readOnRobot();

	double currYaw = this->getRobotPosition().getYaw();
	double wantedYaw = dYaw;
	double firstDeltaYaw = abs(wantedYaw - currYaw);

	double absOffsetOne;

	int side = 0;

	absOffsetOne = currYaw - dYaw;
	if (absOffsetOne < 0) {
		absOffsetOne += M_PI * 2;
	}

	if (absOffsetOne < M_PI) {
		side = -1;
	} else {
		side = 1;
	}

	if (firstDeltaYaw > MINIMUM_ANGLE) {
		_robot->setSpeed(0.0, ROTATION_SPEED * side);
	} else {
		_robot->setSpeed(ROTATION_FORWARD_SPEED, ROTATION_SPEED * side);
	}

	while (true) {
		this->readOnRobot();
		currYaw = this->getRobotPosition().getYaw();

		// Change the curr yaw cuz player yaw is not 0-->6.2 :@
		if (currYaw < 0) {
			currYaw = M_PI + (M_PI + currYaw);
		}
		if (DEBUG) {
			cout << "Wanted angle: " << wantedYaw << " Particle Yaw: "
					<< currYaw << " Robot Yaw: " << _robot->getRealYaw()
					<< " Pdelta: " << abs(wantedYaw - currYaw) << " Rdelta: "
					<< _robot->getDeltaPosition()->getYaw() << endl;
		}

		if (currYaw > wantedYaw - ANGLE_RANGE
				&& currYaw < wantedYaw + ANGLE_RANGE) {
			break;
		}
	}
}

void Manager::readOnRobot() {
	//for (int i = 0; i < 5; i++) {
	_robot->Read();
	//}
	_localizationManager->updateParticles(_robot->getDeltaPosition(),
			_robot->getLaserScan());
}

Position Manager::getRobotPosition() {
	if (PLAYER) {
		return _robot->getPosition();
	}

	return _localizationManager->getHighestBeliefParticle().getPosition();
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}

double Manager::calcDistance(Position currentPosition, Position nextPosition) {
	double deltaRow = abs(currentPosition.getRow() - nextPosition.getRow());
	double deltaCol = abs(currentPosition.getCol() - nextPosition.getCol());

	return sqrt((pow(deltaRow, 2)) + (pow(deltaCol, 2)));
}

double Manager::calcAngleDelta(Position currentPosition,
		Position nextPosition) {

	// calculate the next movement
	int nextDirection = this->calcNextMovement(currentPosition, nextPosition);
	float ang;
	//this->_robot->Read();
	//float currentYawInDegree = (this->_robot->getYaw() * 180) / M_PI;

	// get the angle in radian
	ang = atan2(abs(currentPosition.getRow() - nextPosition.getRow()),
			abs(currentPosition.getCol() - nextPosition.getCol()));
	// change angle to degree
	//ang = (ang * 180) / M_PI;

	switch (nextDirection) {
	case UP_LEFT:
		// calc the delta degree
		ang = M_PI - ang;
		break;
	case UP_RIGHT:
		//ang = M_PI - 1.571 - ang;
		//ang=ang;
		break;
	case DOWN_LEFT:
		//ang = (M_PI - 1.571 - ang) + M_PI;
		ang = M_PI + ang;
		break;
	case DOWN_RIGHT:
		ang = 2 * M_PI - ang;
	case UP:
		ang = ANGLE_UP;
		break;
	case DOWN:
		ang = ANGLE_DOWN;
		break;
	case LEFT:
		ang = ANGLE_LEFT;
		break;
	case RIGHT:
		ang = ANGLE_RIGHT;
		break;

	default:
		return -1;
	}

// change the degree to radian
//ang = (ang * M_PI) / 180;
	return ang;

// calculate the next movement
//	int nextDirection = this->calcNextMovement(currentPosition, nextPosition);
//	double nextAngle;
//
//	// Choose the next angle by the next direction
//	switch (nextDirection) {
//	case UP:
//		nextAngle = ANGLE_UP;
//		break;
//	case DOWN:
//		nextAngle = ANGLE_DOWN;
//		break;
//	case RIGHT:
//		nextAngle = ANGLE_RIGHT;
//		break;
//	case LEFT:
//		nextAngle = ANGLE_LEFT;
//		break;
//	case UP_LEFT:
//		nextAngle = ANGLE_UP_LEFT;
//		break;
//	case UP_RIGHT:
//		nextAngle = ANGLE_UP_RIGHT;
//		break;
//	case DOWN_LEFT:
//		nextAngle = ANGLE_DOWN_LEFT;
//		break;
//	case DOWN_RIGHT:
//		nextAngle = ANGLE_DOWN_RIGHT;
//		break;
//	default:
//		return -1;
//	}
//
//	this->_robot->Read();
//	double deltaAngle = nextAngle - this->_robot->getYaw();

//	return (deltaAngle);
}

int Manager::calcNextMovement(Position currentPosition, Position nextPosition) {
	int direction;

// Check if the next row is above the current (the direction will be DOWN* because the rows grows downward)
	if (nextPosition.getRow() > currentPosition.getRow()) {
		// Check if the next col is right from current
		if (nextPosition.getCol() > currentPosition.getCol()) {
			direction = DOWN_RIGHT;
		}
		// Check if the next col is left from current
		else if (nextPosition.getCol() < currentPosition.getCol()) {
			direction = DOWN_LEFT;
		} else {
			// Same column
			direction = DOWN;
		}
	}

// Check if the next row is below the current (the direction will be UP* because the rows grows downward)
	else if (nextPosition.getRow() < currentPosition.getRow()) {
		// Check if the next col is right from current
		if (nextPosition.getCol() > currentPosition.getCol()) {
			direction = UP_RIGHT;
		}
		// Check if the next col is left from current
		else if (nextPosition.getCol() < currentPosition.getCol()) {
			direction = UP_LEFT;
		} else {
			// Same column
			direction = UP;
		}
	}
// If we reached to here, that means we are on the same row,
// so lets check if the next position is right/left from current position
	else {
		if (nextPosition.getCol() > currentPosition.getCol()) {
			direction = RIGHT;
		} else {
			direction = LEFT;
		}
	}

	return direction;
}

