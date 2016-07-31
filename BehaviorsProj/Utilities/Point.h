/*
 * Point.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
private:
	int _row;
	int _col;
public:
	Point();
	Point(int row, int col);
	void setRow(int row);
	void setCol(int col);
	int getRow();
	int getCol();
	bool isEqual(Point point);
	virtual ~Point();
};

#endif /* POINT_H_ */
