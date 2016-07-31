/*
 * TurnInPlace.h
 *
 *  Created on: Jul 20, 2015
 *      Author: colman
 */

#ifndef TURNINPLACE_H_
#define TURNINPLACE_H_

#include "Behavior.h"

class TurnInPlace: public Behavior {
public:
	TurnInPlace(Robot* robot);
	virtual ~TurnInPlace();
	bool startCond();
	bool stopCond();

};

#endif /* TURNINPLACE_H_ */
