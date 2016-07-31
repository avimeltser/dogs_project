/*
 * Point.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#include "Point.h"

Point::Point(int row, int col) {
	this->_row = row;
	this->_col = col;
}

Point::Point() {
	this->_row = 0;
	this->_col = 0;
}

Point::~Point() {
}

int Point::getCol() {
	return this->_col;
}

int Point::getRow() {
	return this->_row;
}

void Point::setCol(int col) {
	this->_col = col;
}
void Point::setRow(int row) {
	this->_row = row;
}
bool Point::isEqual(Point point) {
	return ((this->getRow() == point.getRow()) &&
			(this->getCol() == point.getCol()));
}
