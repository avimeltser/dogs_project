/*
 * Robot.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(string ip, int port) :
		_pc(ip, port), _pp(&_pc), _lp(&_pc) {

	_lastX = _pp.GetXPos();
	_lastY = _pp.GetYPos();
	_lastYaw = _pp.GetYaw();
	_currX = _pp.GetXPos();
	_currY = _pp.GetYPos();
	_currYaw = _pp.GetYaw();

	double initialRow = -2.875;
	double initialCol = 2.175;
	double initialYaw = 0.349;

	this->UpdatePosition(initialRow, initialCol, initialYaw);

	_pp.SetMotorEnable(true);

	//Fix the player bug
	for (int i = 0; i < 15; i++) {
		this->_pc.Read();
	}
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}
void Robot::Read() {
	_lastX = _currX;
	_lastY = _currY;
	_lastYaw = _currYaw;

	_pc.Read();

	_currX = this->getX();
	_currY = this->getY();
	_currYaw = this->getYaw();
}

void Robot::setSpeed(float linear, float angular) {
	_pp.SetSpeed(linear, angular);
}

void Robot::setXAndY(float x, float y) {
	_lastX = x;
	_lastY = y;
}

float Robot::getCol() {
	return _pp.GetXPos() * 40 + 275;
}

float Robot::getRow() {
	return _pp.GetYPos() * 40 * (-1) + 190;
}

float Robot::getX() {
	return _pp.GetXPos() * 40 + 275;
}

float Robot::getY() {
	return _pp.GetYPos() * 40 * (-1) + 190;
}

float Robot::getYaw() {
	return _pp.GetYaw();
}

float* Robot::getLaserScan() {
	float *scan = new float[_lp.GetCount()];
	for (unsigned int i = 0; i < _lp.GetCount(); i++) {
		scan[i] = _lp[i];
	}
	return scan;
}

int Robot::deg_to_index(double deg) {
	return (deg + 120) / 0.36;
}

Position Robot::getPosition() {
	return Position(this->getY(), this->getX(), this->getYaw());
}

Position* Robot::getDeltaPosition() {

	double deltaRow = this->_currY - this->_lastY;
	double deltaCol = this->_currX - this->_lastX;
	double deltaYaw = this->_currYaw - this->_lastYaw;

	return new Position(deltaRow, deltaCol, deltaYaw);
}

void Robot::ChangeYawRobotPlayer(double dYaw) {
	this->Read();
	double currYaw = this->getYaw();
	double wantedYaw = dYaw;
	double firstDeltaYaw = abs(wantedYaw - currYaw);

	//currYaw += M_PI;
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
		this->setSpeed(0.0, ROTATION_SPEED * side);
	} else {
		this->setSpeed(ROTATION_FORWARD_SPEED, ROTATION_SPEED * side);
	}

	while (true) {
		this->Read();
		currYaw = this->getYaw();

		// Change the curr yaw cuz player yaw is not 0-->6.2 :@
		if (currYaw < 0) {
			currYaw = M_PI + (M_PI + currYaw);
		}

		if (DEBUG) {
			cout << "Wanted angle: " << wantedYaw << " Robot Yaw: " << currYaw
					<< "delta: " << abs(wantedYaw - currYaw) << endl;
		}
		//currYaw += M_PI;

		//if (currYaw > dYaw - 0.06 && currYaw < dYaw + 0.06) {
		if (currYaw > wantedYaw - ANGLE_RANGE
				&& currYaw < wantedYaw + ANGLE_RANGE) {
			//this->setSpeed(0.0, 0.0);
			break;
		}
	}
}

void Robot::UpdatePosition(double row, double col, double yaw) {
	double x = col;
	double y = row;

	//while (_pp.GetXPos() != x || _pp.GetYPos() != y || _pp.GetYPos() != yaw) {
	_pp.SetOdometry(x, y, yaw);
	this->Read();
	//
}
