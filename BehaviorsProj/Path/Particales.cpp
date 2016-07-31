///*
// * Particales.cpp
// *
// *  Created on: Jul 17, 2015
// *      Author: colman
// */
//
//#include "Particales.h"
//
////Constructors of objects type of Particle
//Particales::Particales(float row,float col) {
//	Particales(row,col,0);
//}
//Particales::Particales(float row,float col,float yaw) {
//	Particales(row,col,yaw,1.0);
//}
//Particales::Particales(float row, float col, float yaw, float belief){
//	pRow = row;
//	pCol = col;
//	pYaw = yaw;
//	pBelief = belief;
//}
//
////Method which handles the particle position update
//void Particales::UpdateParticle(float delRow, float delCol, float delYaw, float laserScan[], int laserCount) {
//
//	// moving the particle with the same estimated vector that the robot itself moved
//	pRow += M_TO_CM(delRow);
//	pCol += M_TO_CM(delCol);
//	pYaw += delYaw;
//
//	// updating the belief of the new location!
//	pBelief *=  /* ProbCalc(delX, delY, delYaw) */ ProbUpdateMapByScan(laserScan,laserCount);
//}
//
////Method which calculate the particle's probability by map
//float Particales::ProbUpdateMapByScan(float laserScan[], int laserCount) {
//	float rowObj,colObj;
//	int mismatch = 0;
//	int match = 0;
//	int i,j;
//
//	for (i=0; i<laserCount; i = i+INDEX_PER_DEGREE) {
//
//		// the sensor detects that the road is open
//		if (laserScan[i] > OPEN_PATH_RANGE) {
//
//			for (j=SENSOR_FROM_END; j<=SENSOR_DETECTION_RANGE; j = j+CELL_DIM) {
//				rowObj = (j * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pRow;
//				colObj = (j * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pCol;
//				 if(SimManager::GetInstance()->m_Map->getCell(xObj,yObj)->isCellWalkable()) // the cell is open (like the laser detects)
//					 match++;
//				 else
//					mismatch++;
//			}
//		// the laser detects that the road is closed
//		}else {
//			rowObj = ((M_TO_CM(laserScan[i])) * sin(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pRow;
//			colObj = ((M_TO_CM(laserScan[i])) * cos(DTOR(ConverteIndexToAngle(i,laserCount,LASER_ANGLE_RANGE)) + pYaw)) + pCol;
//			if (SimManager::GetInstance()->m_Map->getCell(xObj,yObj)->isCellWalkable()) // the cell is open (and the laser detects otherwise)
//				mismatch++;
//			else
//				match++;
//		}
//	}
//
//	if ((mismatch + match) == 0)
//		return (float) 0;
//	else
//		return ((float)(match))/(mismatch + match);
//
//}
//
////Method which calculate the particle's probability
//float Particales::ProbCalc(float delRow, float delCol, float delYaw) {
//	float distance = sqrt(pow(delRow,2)+pow(delCol,2));
//	if ((delYaw < NORMAL_ACCURATE_ANGLE_TO_MOVE) && (delYaw > -NORMAL_ACCURATE_ANGLE_TO_MOVE)) {
//		if (distance <= SAFE_DISTANCE_TO_MOVE)
//			return 1.0;
//		else
//			return (SAFE_DISTANCE_TO_MOVE + distance + 0.2);
//	}
//	else if ((delYaw < MAX_ACCURATE_ANGLE_TO_MOVE) && (delYaw > -MAX_ACCURATE_ANGLE_TO_MOVE))
//	{
//		if (distance <= SAFE_DISTANCE_TO_MOVE)
//			return 1.0;
//		else
//			return (SAFE_DISTANCE_TO_MOVE + distance - 0.2);
//	}
//	return 1.0;
//}
//
////Method which return the particle Belief value
//double Particales::GetBelief() {
//	return pBelief;
//}
//
////Method which return the particle X value
//double Particales::GetRow() {
//	return pRow;
//}
//
////Method which return the particle Y value
//double Particales::GetCol() {
//	return pCol;
//}
//
////Method which return the particle Yaw value
//double Particales::GetYaw() {
//	return pYaw;
//}
//
////Method which converts laser index to angle
//float Particales::ConverteIndexToAngle(int index, int x, int radius) {
//	return ((float)index*((float)radius/x))-radius/2.0;
//}
//
////Destructor of objects type of Particle
//Particales::~Particales() {
//}
