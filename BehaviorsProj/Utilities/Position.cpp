/*
 * Position.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#include "Position.h"

Position::Position()
{
	this->_row = 0;
	this->_col = 0;
	this->_yaw = 0;
}

Position::Position(double row, double col, double yaw)
{
	this->_row = row;
	this->_col = col;
	this->_yaw = yaw;
}

Position::~Position()
{
}

double Position::getRow()
{
	return this->_row;
}

double Position::getCol()
{
	return this->_col;
}

double Position::getYaw()
{
	return this->_yaw;
}

void Position::setRow(double row)
{
	this->_row = row;
}

void Position::setCol(double col)
{
	this->_col = col;
}
void Position::setYaw(double yaw)
{
	this->_yaw = yaw;
}
