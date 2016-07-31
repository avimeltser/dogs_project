/*
 * Particle.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "Particle.h"

Particle::Particle(double row, double col, double yaw, float belief, Map* map) {
	this->_position = Position(row, col, yaw);
	this->_belief = belief;
	this->_map = map;
}

Particle::Particle(Position pos, float belief, Map* map) {
	this->_position = pos;
	this->_belief = belief;
	this->_map = map;

	this->_position = createPositionRandomly(pos);

	// run until we get particle not on block
	while (this->_map->getMap()[(int) _position.getRow()][(int) _position.getCol()]
			== BLOCK) {
		this->_position = createPositionRandomly(pos);
	}
}

Position Particle::getPosition() {
	return this->_position;
}

double Particle::getRow() {
	return _position.getRow();
}
double Particle::getCol() {
	return _position.getCol();
}
double Particle::getYaw() {
	return _position.getYaw();
}

float Particle::getBelief() {
	return this->_belief;
}

Position Particle::createPositionRandomly(Position currentPosition) {

	// Calc range of delta particle
	int rowRange = floor(_map->getHeight() / 2 * PARTICLE_RADIUS);
	int colRange = floor(_map->getWidth() / 2 * PARTICLE_RADIUS);
	double YawRange = M_PI * 2 / 2 * 0.1;

	int intYawRange = YawRange * 10000;

	int deltaRow = (rand() % (2 * rowRange)) - rowRange;
	int deltaCol = (rand() % (2 * colRange)) - colRange;
	double deltaYaw = (rand() % (2 * intYawRange)) - intYawRange;

	deltaYaw = deltaYaw / 10000;

	Position randomLocation = Position(currentPosition.getRow() + deltaRow,
			currentPosition.getCol() + deltaCol,
			currentPosition.getYaw() + deltaYaw);

	return randomLocation;
}

Particle Particle::createParticle() {
	// Generate particle (the constructor of particle(position) creates random particle
	return Particle(_position, _belief * 0.9, _map);
}

float Particle::UpdateParticle(double dRow, double dCol, double dYaw,
		float laserArray[]) {
	this->_position.setRow(this->_position.getRow() + dRow);
	this->_position.setCol(this->_position.getCol() + dCol);
	this->_position.setYaw(this->_position.getYaw() + dYaw);

	float predBel = ProbByMove(dRow, dCol, dYaw) * this->_belief;
	this->_belief = MIU_FOR_BELIEF * ProbByLaser(laserArray) * predBel;

	if (this->_belief > 1) {
		this->_belief = 1;
	}

//	if (DEBUG) {
//		cout << "UpdateParticle belief: " << _belief << endl;
//	}

	return this->_belief;
}

float Particle::ProbByMove(double dRow, double dCol, double dYaw) {
	// cm?
	float distance = sqrt(pow(dCol, 2) + pow(dRow, 2));
	float prob = 0;

	// Check if the robot moved really really little bit
	if (distance < 0.2 && abs(dYaw) < 0.1) {
		return 0.9;
	}

	if (distance < 0.4 && abs(dYaw) < 0.2) {
		return 0.7;
	}

	if (distance < 0.7 && abs(dYaw) < 0.3) {
		return 0.4;
	}

	return 0.3;

	/*prob = 1 - ((distance / MAX_DISTANCE) * (dYaw / LASER_MAX_DEGREE));
	 if (prob > 1)
	 prob = 1;

	 return prob;*/

}

float Particle::ProbByLaser(float laserArray[]) {
	int correctReadingAmount, totalReadingAmount;

	// Run over laser scan
	for (unsigned int laserRead = 0; laserRead < LASER_READS_AMOUNT;
			laserRead += 10) {
		totalReadingAmount++;
		float laserScan = laserArray[laserRead];

		// Free (don't see anything!)
		//if (laserScan > MAX_LEASER_DISTANCE - 0.2) {
		correctReadingAmount += checkIfLaserDetectRight(laserScan, laserRead);
	}

	return correctReadingAmount / totalReadingAmount;
}

int Particle::checkIfLaserDetectRight(float laserScanValue, int laserRead) {
	/*float max_angle_of_read = 240 / 0.36; //666.66667
	 float half_max_angle_of_read = max_angle_of_read / 2;

	 //(half_max_angle_of_read) - (half_max_angle_of_read - laserRead)	//angle = 0.36 * (2 * half_max_angle_of_read + laserRead) - 120;
	 */

	// clac the angle of laser from robot nose
	float angle;
	angle = floor(0.36 * laserRead - 120);

	/* Old, maybe works..
	 // Laser degree as an offset, plus or minus depends on the laser scan start direction
	 //float spottedPointYaw = M_PI - DEGREE_TO_RADIAN(_position.getYaw() + laserRead);
	 */

	// calc the robot yaw if we want to look to the current laserRead
	float spottedPointYaw = _position.getYaw() + DEGREE_TO_RADIAN(angle);

	float laserScanValueInCM = METER_TO_CM(laserScanValue);

	float cosofSpottedPoint = cos(spottedPointYaw);
	float sinofSpottedPoint = -sin(spottedPointYaw);

	// run from robot position until laserScanValue Distance
	for (int distanceFromSpottedPointInCM = 1;
			distanceFromSpottedPointInCM < floor(laserScanValueInCM);
			distanceFromSpottedPointInCM += CM_TO_CHECK_LASER) {

		// Calculating the spotted point delta position
		// I think it works only for angle of top right
		float deltaCol = cosofSpottedPoint * distanceFromSpottedPointInCM;
		float deltaRow = sinofSpottedPoint * distanceFromSpottedPointInCM;

		// transform delta from cm to pixels
		deltaCol = deltaCol * _map->getMapResolution();
		deltaRow = deltaRow * _map->getMapResolution();

		// create the spotted point from particle current position + delta
		Point spottedPoint(round(_position.getCol() + deltaCol),
				round(_position.getRow()) + deltaRow);

		// check if the spotted point is in the map
		if ((spottedPoint.getCol() >= 0
				&& spottedPoint.getCol() < _map->getWidth())
				&& (spottedPoint.getRow() >= 0
						&& spottedPoint.getRow() < _map->getHeight())) {

			// get the value of point from map
			int spottedPointValue =
					_map->getMap()[spottedPoint.getRow()][spottedPoint.getCol()];

			// check if the spotted point is block and we are NEAR the laserScanValueInCM
			if (spottedPointValue == BLOCK) {
				if (abs(
						laserScanValueInCM
								- distanceFromSpottedPointInCM) < PARTICLE_LASER_NOISE_IN_CM) {
					return 1;
				}

				// check if the spotted point is block and we are FAR AWAY from laserScanValueInCM
				if (abs(
						laserScanValueInCM
								- distanceFromSpottedPointInCM) > PARTICLE_LASER_NOISE_IN_CM) {
					return 0;
				}
				/*// check if the spotted point is FREE and we are NEAR from laserScanValueInCM
				 else if (spottedPointValue == FREE
				 && abs(laserScanValueInCM - distanceFromSpottedPointInCM)
				 < PARTICLE_LASER_NOISE_IN_CM) {

				 }*/
			}
		}
		//end of for
	}

	// if we reached here, we didnt see block in map
	if (abs(
			laserScanValueInCM - MAX_LEASER_DISTANCE) > PARTICLE_LASER_NOISE_IN_CM) {
		return 0;
	}

	return 1;
}

Particle::~Particle() {
// TODO Auto-generated destructor stub
}

