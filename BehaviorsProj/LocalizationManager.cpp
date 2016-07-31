/*
 * LocalizationManager.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(Position * startPosition, Map * map) {
	_map = map;
	srand(time(NULL));

	_storePosition = Position(startPosition->getRow(), startPosition->getCol(),
			startPosition->getYaw());

	// create particles from start position
	Particle startParticle = Particle(startPosition->getRow(),
			startPosition->getCol(), startPosition->getYaw(), (float) (1),
			this->_map);
	this->createParticlesFromParticle(startParticle, true);
	//_particles.insert(_particles.end(), childParticles.begin(), childParticles.end());
}

void LocalizationManager::createParticlesFromParticle(Particle fromParticle,
		bool isVectorEmpty) {

	if (isVectorEmpty == true) {
		// add start position
		this->_particles.push_back(fromParticle);
	}

	int particalesToCreate = MAX_PARTICLE - this->_particles.size();
	// create particles from best particle, the amount will be (MAX_PARTICLE - amount we have)
	for (int index = 0; index < particalesToCreate; index++) {
		_particles.push_back(fromParticle.createParticle());
	}
}

Particle LocalizationManager::getHighestBeliefParticle() {

	Particle bestParticle = _particles[0];

	// run over the particles
	//for (particlesIterator = _particles.begin(); particlesIterator != _particles.end(); ++particlesIterator) {
	for (int index = 0; index < _particles.size(); index++) {
		// check if we got better particle
		if (_particles[index].getBelief() > bestParticle.getBelief())
			bestParticle = _particles[index];
	}

	return bestParticle;
}

void LocalizationManager::updateParticles(Position * deltaPosition,
		float laserScan[]) {

	// store the position for restore
	_storePosition.setRow(_storePosition.getRow() + deltaPosition->getRow());
	_storePosition.setCol(_storePosition.getCol() + deltaPosition->getCol());
	_storePosition.setYaw(_storePosition.getYaw() + deltaPosition->getYaw());

	for (vector<Particle>::iterator partic = _particles.begin();
			partic != _particles.end();) {
		if (partic->UpdateParticle(deltaPosition->getRow(),
				deltaPosition->getCol(), deltaPosition->getYaw(),
				laserScan) < BELIEF_TRASHHOLD) {
			_particles.erase(partic);
		} else {
			partic++;
		}
	}

	if (DEBUG) {
		cout << "Number of particals after delete: " << _particles.size()
				<< endl;
	}

	// all particle died, so we need to create new particle from storePosition
	if (_particles.size() == 0) {
		// create particles from start position
		Particle startParticle = Particle(this->_storePosition.getRow(),
				this->_storePosition.getCol(), this->_storePosition.getYaw(),
				(float) (1), this->_map);
		this->createParticlesFromParticle(startParticle, true);
	} else {
		Particle bestPractical = getHighestBeliefParticle();
		if (DEBUG) {
			cout << "Best partical's values: " << bestPractical.getCol() << bestPractical.getRow()
					<< bestPractical.getBelief();
		}

		this->createParticlesFromParticle(bestPractical, false);
	}
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}

