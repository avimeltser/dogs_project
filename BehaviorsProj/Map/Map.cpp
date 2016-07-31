/*
 * Map.cpp
 *
 *  Created on: xun 12, 2015
 *      Author: colman
 */

#include <string>
#include <string.h>
#include "Map.h"

using namespace std;

Map::Map(RobotParameters& params) {
	//the raw pixels
	vector<unsigned char> image;

	unsigned width, height;

	// Geting the file path
	this->_filename = params.GetMapPath();

	// Decoding the image from the path we got earlier
	unsigned error = lodepng::decode(image, width, height, this->_filename);

	this->_width=width;
	this->_height = height;

	// If there's an error loading the image, display it
	if (error)
		cout << "decoder error " << error << ": " << lodepng_error_text(error)
				<< endl;

	this->_map = new int*[height];

	// init map
	for (int i = 0; i < height; i++) {
		this->_map[i] = new int[width];
	}

	// Running over the image and transform it to matrix
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (image[y * width * 4 + x * 4 + 0]
					|| image[y * width * 4 + x * 4 + 1]
					|| image[y * width * 4 + x * 4 + 2])
				_map[y][x] = FREE;
			else
				_map[y][x] = BLOCK;
		}
	}

	// Getting the map resolution
	_mapResolution = params.GetMapResolution();
	// Getting the grid resolution
	int gridResolution = params.GetGridResolution();

	// Getting the robot size x,y
	int robot_size_x, robot_size_y;
	params.GetRobotSize(robot_size_x, robot_size_y);

	// creating the the puff size
	int puffSize = ceil(max(robot_size_x, robot_size_y) / _mapResolution/ 2);
			//+ 2;

	// Creating large map for puff the original map
	this->_largeMap = new int*[height];
	// init large map
	for (int i = 0; i < height; ++i) {
		this->_largeMap[i] = new int[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			this->_largeMap[i][j] = FREE;
		}
	}

	//int largeMap[height][width];

	// Running over the matrix map and puffy it
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// Check if there is black cell
			if (_map[y][x] == BLOCK) {

				// Run over the cell to puff
				for (int pY = y - puffSize; pY < y + puffSize; pY++) {
					// Check if we didnt exceed the matrix
					if (pY >= 0 && pY < height) {
						for (int pX = x - puffSize; pX < x + puffSize; pX++) {
							// Check if we didnt exceed the matrix
							if (pX >= 0 && pX < width) {
								this->_largeMap[pY][pX] = BLOCK;
							}
						}
					}
				}
			}
		}
	}

	//printing the large matrix to file to check it
	FILE* f = fopen("mapPuffy.txt", "w");
	if (f == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			fprintf(f, "%d", this->_largeMap[y][x]);
			//cout << map[y][x];
		}
		fprintf(f, "\n");
		//cout << endl;
	}
	fclose(f);

	int grid_height = (height * _mapResolution) / gridResolution;
	int grid_width = (width * _mapResolution) / gridResolution;

	int** grid = new int*[grid_height];

	// init grid
	for (int i = 0; i < grid_height; i++) {
		grid[i] = new int[grid_width];
	}

	//int grid[grid_height][grid_width];

	int scaleLargeToGrid = gridResolution / _mapResolution;

	// Running over the puff map and transform it to grid
	for (int y = 0; y < grid_height; y++) {
		for (int x = 0; x < grid_width; x++) {
			bool isBlack = false;

			// Run over the cell to check if there is any black cell
			for (int pY = y * scaleLargeToGrid;
					pY < y * scaleLargeToGrid + scaleLargeToGrid; pY++) {
				// Check if we didnt exceed the matrix
				if (pY >= 0 && pY < height && isBlack == false) {
					for (int pX = x * scaleLargeToGrid;
							pX < x * scaleLargeToGrid + scaleLargeToGrid;
							pX++) {
						// Check if we didnt exceed the matrix
						if (pX >= 0 && pX < width) {
							if (this->_largeMap[pY][pX] == BLOCK) {
								isBlack = true;
								break;
							}
						}
					}
				}
			}

			// if one of the 4 (scaleLargeToGrid) is black, we paint the grid cell to black
			if (isBlack) {
				grid[y][x] = BLOCK;
			} else {
				grid[y][x] = FREE;
			}
		}
	}

	Position startPosition = Position(
			((params.GetStartLocation().getRow() * _mapResolution) / gridResolution),
			((params.GetStartLocation().getCol() * _mapResolution) / gridResolution),
			params.GetStartLocation().getYaw());

	Point goalPoint = Point(
			((params.GetGoalLocation().getRow() * _mapResolution) / gridResolution),
			((params.GetGoalLocation().getCol() * _mapResolution) / gridResolution));

	this->_grid = Grid(grid_height, grid_width, gridResolution, height, width,
			startPosition, goalPoint);
	this->_grid.initGridByMatrix(grid);

}

Grid Map::getGrid() {
	return this->_grid;
}

int** Map::getMap() {
	return this->_map;
}

int Map::getWidth() {
	return this->_width;
}
int Map::getHeight() {
	return this->_height;
}

void Map::loadMap() {

}
double Map::getMapResolution() {
	return _mapResolution;
}
Map::~Map() {
	// TODO Auto-generated destructor stub
}
