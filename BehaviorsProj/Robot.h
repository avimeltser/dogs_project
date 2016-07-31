/*
 * Robot.h
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include <string>
#include "Utilities/Global.h"
#include "Utilities/Position.h"
using namespace PlayerCc;

class Robot {
private:
	PlayerClient _pc;
	Position2dProxy _pp;
	LaserProxy _lp;

	float _lastX, _lastY, _lastYaw;
	float _currX, _currY, _currYaw;

public:
	Robot(string ip, int port);
	virtual ~Robot();

	void setSpeed(float linear, float angular);
	float getCol();
	float getRow();

	float getX();
	float getY();
	float getYaw();

	float getRealX();
	float getRealY();
	float getRealYaw();

	Position*  getDeltaPosition();

	void ChangeYawRobotPlayer(double dYaw);
	void UpdatePosition(double x, double y, double yaw);



	void Read();

	float* getLaserScan();
	int deg_to_index(double deg);

	Position getPosition();

	void setXAndY(float x, float y);

};

#endif /* ROBOT_H_ */
