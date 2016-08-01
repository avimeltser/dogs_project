#include <libplayerc++/playerc++.h>
#include <iostream>
#include <math.h>
#include "Robot.h"
#include "ConfigurationManager.h"
#include "Map/Map.h"
#include "Map/Grid.h"
#include "Path/PathSearcher.h"
#include "Manager.h"
#include "LocalizationManager.h"
#include "Particle.h"
#include "Plans/PlnObstacleAvoid.h"
#include "Utilities/Position.h"
#include "Utilities/Global.h"
#include "Utilities/Point.h"

using namespace PlayerCc;


void readOnRobot(Robot& robot, LocalizationManager& localizationManager) {
	robot.Read();
	localizationManager.updateParticles(robot.getDeltaPosition(), robot.getLaserScan());
}


Position getRobotPosition(LocalizationManager& localizationManager) {
	return localizationManager.getHighestBeliefParticle().getPosition();
}

void changeYawRobot(double dYaw, Robot& robot, LocalizationManager& localizationManager) {
	readOnRobot(robot, localizationManager);

	double currYaw = localizationManager.getHighestBeliefParticle().getPosition().getYaw();
	double wantedYaw = dYaw;
	double firstDeltaYaw = abs(wantedYaw - currYaw);

	double absOffsetOne;

	int side = 0;

	absOffsetOne = currYaw - dYaw;
	if (absOffsetOne < 0) {
		absOffsetOne += M_PI * 2;
	}

	if (absOffsetOne < M_PI) {
		side = -1;
	} else {
		side = 1;
	}

	if (firstDeltaYaw > MINIMUM_ANGLE) {
		robot.setSpeed(0.0, ROTATION_SPEED * side);
	} else {
		robot.setSpeed(ROTATION_FORWARD_SPEED, ROTATION_SPEED * side);
	}

	while (true) {
		readOnRobot(robot, localizationManager);
		currYaw = getRobotPosition(localizationManager).getYaw();

		// Change the curr yaw cuz player yaw is not 0-->6.2 :@
		if (currYaw < 0) {
			currYaw = M_PI + (M_PI + currYaw);
		}

		if (currYaw > wantedYaw - ANGLE_RANGE
				&& currYaw < wantedYaw + ANGLE_RANGE) {
			break;
		}
	}
}

double calcDistance(Position currentPosition, Position nextPosition) {
	double deltaRow = abs(currentPosition.getRow() - nextPosition.getRow());
	double deltaCol = abs(currentPosition.getCol() - nextPosition.getCol());

	return sqrt((pow(deltaRow, 2)) + (pow(deltaCol, 2)));
}

int calcNextMovement(Position currentPosition, Position nextPosition) {
	int direction;

	// Check if the next row is above the current (the direction will be DOWN* because 	the rows grows downward)
	if (nextPosition.getRow() > currentPosition.getRow()) {
		// Check if the next col is right from current
		if (nextPosition.getCol() > currentPosition.getCol()) {
			direction = DOWN_RIGHT;
		}
		// Check if the next col is left from current
		else if (nextPosition.getCol() < currentPosition.getCol()) {
			direction = DOWN_LEFT;
		} else {
			// Same column
			direction = DOWN;
		}
	}

	// Check if the next row is below the current (the direction will be UP* because the rows grows downward)
	else if (nextPosition.getRow() < currentPosition.getRow()) {
		// Check if the next col is right from current
		if (nextPosition.getCol() > currentPosition.getCol()) {
			direction = UP_RIGHT;
		}
		// Check if the next col is left from current
		else if (nextPosition.getCol() < currentPosition.getCol()) {
			direction = UP_LEFT;
		} else {
			// Same column
			direction = UP;
		}
	}
	// If we reached to here, that means we are on the same row,
	// so lets check if the next position is right/left from current position
	else {
		if (nextPosition.getCol() > currentPosition.getCol()) {
			direction = RIGHT;
		} else {
			direction = LEFT;
		}
	}

	return direction;
}

double calcAngleDelta(Position currentPosition,
		Position nextPosition) {
	// calculate the next movement
	int nextDirection = calcNextMovement(currentPosition, nextPosition);
	float ang;

	// get the angle in radian
	ang = atan2(abs(currentPosition.getRow() - nextPosition.getRow()),
			abs(currentPosition.getCol() - nextPosition.getCol()));

	switch (nextDirection) {
	case UP_LEFT:
		// calc the delta degree
		ang = M_PI - ang;
		break;
	case UP_RIGHT:
		//ang = M_PI - 1.571 - ang;
		//ang=ang;
		break;
	case DOWN_LEFT:
		//ang = (M_PI - 1.571 - ang) + M_PI;
		ang = M_PI + ang;
		break;
	case DOWN_RIGHT:
		ang = 2 * M_PI - ang;
	case UP:
		ang = ANGLE_UP;
		break;
	case DOWN:
		ang = ANGLE_DOWN;
		break;
	case LEFT:
		ang = ANGLE_LEFT;
		break;
	case RIGHT:
		ang = ANGLE_RIGHT;
		break;

	default:
		return -1;
	}

// change the degree to radian
//ang = (ang * M_PI) / 180;
	return ang;
}

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
/*
// Robot
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
	
	double initialRow = -2.875;
	double initialCol = 2.175;
	double initialYaw = 0.349;

	for (int i = 0; i < 20; i++) {
		robot.UpdatePosition(initialRow, initialCol, initialYaw);
		robot.Read();
	}
	
	PathSearcher* ps = new PathSearcher(grid);

	vector<Point> path = ps->searchPath(grid.getStartPoint(),
			grid.getGoalPoint());

	vector<Position> waypoint = ps->getWayPoints();

	LocalizationManager localizationManager(startPosition, &map);

	vector<Position> waypointCopy = ps->getWayPoints();
	
	unsigned wayPointIndex = 1;
	
	Position nextPosition = waypointCopy[wayPointIndex];

	// Change the movement direction of the robot
	double angle = calcAngleDelta(localizationManager.getHighestBeliefParticle().getPosition(), nextPosition);

	changeYawRobot(angle, robot, localizationManager);

	robot.setSpeed(FORWARD_SPEED, 0);

	double distance, currentDistance;

	// Run until we didnt reached the last waypoint (goal)
	while (wayPointIndex < waypointCopy.size()) {
		readOnRobot(robot, localizationManager);

		// Calcuate the metric distance between the robot and next position
		distance = calcDistance(getRobotPosition(localizationManager), nextPosition);

		// Check if the distance of the robot the next waypoint is less than the minimum distance
		if (distance <= MINIMUM_DISTANCE) {
			// Get the next waypoint
			wayPointIndex++;

			// Check if we reached the last waypoint (goal)
			if (wayPointIndex == waypointCopy.size()) {
				break;
			}
			nextPosition = waypointCopy[wayPointIndex];

			// Change the movement direction of the robot
			double angle = calcAngleDelta(getRobotPosition(localizationManager),
					nextPosition);

			changeYawRobot(angle, robot, localizationManager);

			robot.setSpeed(FORWARD_SPEED, 0);
		} 
	}
	
	return 0;
}
*/
// Player
int main() {
	static ConfigurationManager conf;

	int colStart, rowStart;
	double yawStart;
	ConfigurationManager::getStartLocation(colStart, rowStart, yawStart);
	yawStart = DEGREE_TO_RADIAN(yawStart);

	Position * startPosition = new Position(rowStart, colStart, yawStart);

	Map map = Map();
	Grid grid = map.getGrid();

	Robot robot("localhost", 6665);

	robot.Read();

	double initialRow = -2.875;
	double initialCol = 2.175;
	double initialYaw = 0.785;

	for (int i = 0; i < 20; i++) {
		robot.UpdatePosition(initialRow, initialCol, initialYaw);
		robot.Read();
	}

	PathSearcher* ps = new PathSearcher(grid);

	vector<Point> path = ps->searchPath(grid.getStartPoint(),
			grid.getGoalPoint());
			
	vector<Position> waypoint = ps->getWayPoints();

	LocalizationManager * localizationManager = new LocalizationManager(startPosition, &map);

	vector<Position> waypointCopy = ps->getWayPoints();
	
	unsigned wayPointIndex = 1;

	for (int i = 0; i < 20; i++)
	{
		robot.Read();
	}

	Position nextPosition = waypointCopy[wayPointIndex];

	// Change the movement direction of the robot
	double angle = calcAngleDelta(robot.getPosition(), nextPosition);
	robot.ChangeYawRobotPlayer(angle);

	double distance, currentDistance;

	// Run until we didnt reached the last waypoint (goal)
	while (wayPointIndex < waypointCopy.size()) {
		robot.Read();

		// Calcuate the metric distance between the robot and next position
		distance = calcDistance(robot.getPosition(), nextPosition);

		// Check if the distance of the robot the next waypoint is less than the minimum distance
		if (distance <= MINIMUM_DISTANCE) {

			wayPointIndex++;

			// Check if we reached the last waypoint (goal)
			if (wayPointIndex == waypointCopy.size()) {
				break;
			}
			nextPosition = waypointCopy[wayPointIndex];

			// Change the movement direction of the robot
			double angle = calcAngleDelta(robot.getPosition(),
					nextPosition);
			robot.ChangeYawRobotPlayer(angle);
		} else {
			robot.setSpeed(FORWARD_SPEED, 0);
		}
	}
	
	return 0;
}
