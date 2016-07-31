/*
 * Particle.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#define METER_TO_CM(meter)				(meter * 100)

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include "Utilities/Global.h"
#include "Utilities/Position.h"
#include "Map/Map.h"

class Particle {
private:
	Position _position;
	Map* _map;
	float _belief;

public:
	Particle(double row, double col, double yaw, float belief, Map* map);
	Particle(Position pos, float belief, Map* map);
	virtual ~Particle();

	Position getPosition();
	double getRow();
	double getCol();
	double getYaw();

	float getBelief();
	Position createPositionRandomly(Position currentPosition);
	Particle createParticle();
	float UpdateParticle(double dRow,double dCol,double dYaw, float laserArray[]);

	float ProbByMove(double dRow,double dCol,double dYaw);
	float ProbByLaser(float laserArray[]);
	int checkIfLaserDetectRight(float laserScan, int laserRead);


};

#endif /* PARTICLE_H_ */
