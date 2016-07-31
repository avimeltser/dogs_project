/*
 * Map.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <algorithm>
#include <math.h>
#include "lodepng.h"
#include "../ConfigurationManager.h"
#include "Grid.h"
#include "../Utilities/Global.h"

class Map {
private:
	int** _map;
	int** _largeMap;
	Grid _grid;
	string _filename;
	int _width;
	int _height;
	double _mapResolution;

public:
	Map();
	void loadMap();
	virtual ~Map();

	Grid getGrid();
	int** getMap();

	int getWidth();
	int getHeight();
	double getMapResolution();

};

#endif /* MAP_H_ */
