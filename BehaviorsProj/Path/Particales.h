///*
// * Particales.h
// *
// *  Created on: Jul 17, 2015
// *      Author: colman
// */
//
//#ifndef PARTICALES_H_
//#define PARTICALES_H_
//
//#define MAX_ACCURATE_ANGLE_TO_MOVE 1.0
//#define NORMAL_ACCURATE_ANGLE_TO_MOVE 0.5
//#define SAFE_DISTANCE_TO_MOVE 0.3
//#define NORMALIZEDFACTOR 2
//#define LASER_MAX_RANGE 4.095
//#define LASER_ANGLE_RANGE 240
//#define OPEN_PATH_RANGE 0.75
//#define RTOD(r)   ((r) * 180 / M_PI)
//#define DTOR(d)   ((d) * M_PI / 180)
//#define NORMALIZE(z)   atan2(sin(z), cos(z))
//#define M_TO_CM(m)   (m * 100)
//#define ROBOT_DIM 2
//#define SENSOR_FROM_END 15
//#define SENSOR_DETECTION_RANGE 60
//#define CELL_DIM 5
//#define INDEX_PER_DEGREE 6
//#define MAX_DEGREE 360
//
//#include "../Utilities/Global.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <iostream>
//#include <time.h>
//
//class Particales {
//public:
//	double pRow;
//	double pCol;
//	double pYaw;
//	double pBelief;
//
//	//Constructors of objects type of Particle
//	Particales(float row, float col);
//	Particales(float row, float col, float yaw);
//	Particales(float row, float col, float yaw, float belief);
//
//	//Method which handles the particle position update
//	void UpdateParticle(float delRow, float delCol, float delYaw, float laserScan[],
//			int laserCount);
//
//	//Method which calculate the particle's probability by map
//	float ProbUpdateMapByScan(float laserScan[], int laserCount);
//
//	//Method which calculate the particle's probability
//	float ProbCalc(float delRow, float delCol, float delTetha);
//
//	double GetBelief();
//
//	double GetRow();
//
//	double GetCol();
//
//	double GetYaw();
//
//	//Method which converts laser index to angle
//	float ConverteIndexToAngle(int index, int x, int radius);
//
//	// Destructor of objects type of Particle
//	//~Particales();
//	virtual ~Particales();
//};
//
//#endif /* PARTICALES_H_ */
