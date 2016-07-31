#ifndef READROBOTPARAMETERS_H_
#define READROBOTPARAMETERS_H_

#include <string>
#include "Utilities/Position.h"
#include "Utilities/Global.h"
#include "Utilities/Point.h"

class RobotParameters
{
public:
	RobotParameters(char* config_file_path);
	string GetMapPath();
	Position GetStartLocation();
	Point GetGoalLocation();
	void GetRobotSize(int&x ,int &y);
	double GetMapResolution();
	int GetGridResolution();
	virtual ~RobotParameters();
private:
	Position start;
	Point goal;
	int robot_size_x;
	int robot_size_y;
	double grid_res;
	int map_res;
	std::string map_path;
};
#endif
