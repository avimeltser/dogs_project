/*
 * LocalizationManager.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include "Plans/PlnObstacleAvoid.h"
#include "Robot.h"
#include "Utilities/Position.h"
#include "Utilities/Global.h"
#include "Utilities/Point.h"
#include "Particle.h"
#include "Map/Map.h"
#include <vector>
#include <math.h>

class LocalizationManager {
private:
	vector<Particle> _particles;
	Map * _map;
	Position _storePosition;

	void addParticleFromVector(const vector<Particle>& childParticles);
	void createParticlesFromParticle(Particle fromParticle, bool isVectorEmpty);

public:
//	LocalizationManager();
	LocalizationManager(Position * startPosition, Map * map);
	virtual ~LocalizationManager();
	Particle getHighestBeliefParticle();
	void updateParticles(Position * deltaPosition, float laserScan[]);
};

#endif /* LOCALIZATIONMANAGER_H_ */
