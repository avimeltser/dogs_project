/*
 * TurnInPlace.cpp
 *
 *  Created on: Jul 20, 2015
 *      Author: colman
 */

#include "TurnInPlace.h"

TurnInPlace::TurnInPlace(Robot* robot):Behavior(robot){
	// TODO Auto-generated constructor stub

}

TurnInPlace::~TurnInPlace() {
	// TODO Auto-generated destructor stub
}

bool TurnInPlace::startCond()
{
	if(DEBUG){
		cout << "TurnInPlace start cond triggered" << std::endl;
	}

	return true;
}

bool TurnInPlace::stopCond()
{
	/*
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

	for (int i= Helper::DegreesToIndex(-60) ; i<(Helper::DegreesToIndex(60)) ; i++)
	{
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
		{
			cout << "TurnInPlace stop cond triggered" << endl;
			return false;
		}

	}

	_robot->setSpeed(0.0,0.0);*/

	return true;

}
