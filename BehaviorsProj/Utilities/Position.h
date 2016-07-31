/*
 * Position.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {
private:
	double _row;
	double _col;
	double _yaw;
public:
	Position();
	Position(double row, double col, double yaw);
	virtual ~Position();

	double getRow();
	double getCol();
	double getYaw();
	void setRow(double row);
	void setCol(double col);
	void setYaw(double yaw);
};

#endif /* POSITION_H_ */
