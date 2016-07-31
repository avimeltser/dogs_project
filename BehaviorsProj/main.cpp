#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Robot.h"
#include "ConfigurationManager.h"
#include "Map/Map.h"
#include "Map/Grid.h"
#include "Path/PathSearcher.h"
#include "Manager.h"
#include "LocalizationManager.h"
#include "Particle.h"

using namespace PlayerCc;

void prindGridWithAstar(vector<Point> path, Grid grid) {
	//Test the A* path
	for (int i = 0; i < path.size(); i++) {
		grid.setCellValue(path[i].getRow(), path[i].getCol(), 8);
	}
	grid.setCellValue(grid.getStartPoint().getRow(),
			grid.getStartPoint().getCol(), START_CELL);
	grid.setCellValue(grid.getGoalPoint().getRow(),
			grid.getGoalPoint().getCol(), GOAL_CELL);
	//printing the grid to file to check it
	FILE* fgrid = fopen("grid.txt", "w");
	if (fgrid == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	for (int y = 0; y < grid.getRows(); y++) {
		for (int x = 0; x < grid.getCols(); x++) {
			if (grid.getCellValue(y, x) == 8)
				fprintf(fgrid, "*");
			else
				fprintf(fgrid, "%d", grid.getCellValue(y, x));
			//cout << map[y][x];
		}
		fprintf(fgrid, "\n");
		//cout << endl;
	}
	fclose(fgrid);
}

int main() {
	static ConfigurationManager conf;

	int colStart, rowStart;
	double yawStart;
	ConfigurationManager::getStartLocation(colStart, rowStart, yawStart);
	yawStart = DEGREE_TO_RADIAN(yawStart);

	Position * startPosition = new Position(rowStart, colStart, yawStart);

	Map map = Map();
	Grid grid = map.getGrid();

	Robot robot(ROBOT_IP, 6665);

	robot.Read();

	if (DEBUG) {
		cout << "Robot real read: (row, col, yaw) (" << robot.getRealY() << ", "
				<< robot.getRealX() << ", " << robot.getRealYaw() << ")"
				<< endl;
	}

	double initialRow = -2.875;
	double initialCol = 2.175;
	double initialYaw = 0.349;

	for (int i = 0; i < 20; i++) {
		robot.UpdatePosition(initialRow, initialCol, initialYaw);
		robot.Read();
	}

	if (DEBUG) {
		cout << "Robot real read: (row, col, yaw) (" << robot.getRealY() << ", "
				<< robot.getRealX() << ", " << robot.getRealYaw() << ")"
				<< endl;
		cout << "Robot image read: (row, col, yaw) (" << robot.getY() << ", "
				<< robot.getX() << ", " << robot.getYaw() << ")" << endl;
	}

	PathSearcher* ps = new PathSearcher(grid);

	vector<Point> path = ps->searchPath(grid.getStartPoint(),
			grid.getGoalPoint());

	if (DEBUG) {
		//Test the A* path
		prindGridWithAstar(path, grid);
	}

	vector<Position> waypoint = ps->getWayPoints();

	// TODO: Print to file (image type) the grid with the way point on it
	//grid.setColorizeWaypoints(map.getPuffedMap(),map.getWidth(),map.getHeight(), ps->getRealPath());

	if (DEBUG) {
		// print waypoint for debug
		for (unsigned i = 0; i < waypoint.size(); i++) {
			cout << "( " << waypoint[i].getRow() << " , "
					<< waypoint[i].getCol() << " )" << endl;
		};
	}

	LocalizationManager * localizationManager = new LocalizationManager(startPosition, &map);

	Manager * mgr = new Manager(&robot, ps->getWayPoints(),
			localizationManager);

	if (PLAYER) {
		mgr->runOnPlayer();
	} else {
		mgr->runOnRobot();
	}
	return 0;
}
