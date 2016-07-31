/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

RobotParameters::RobotParameters(char* path)
{
	  string line;
	  ifstream myfile(path);

	  if (myfile.is_open())
	  {
	    while ( getline (myfile,line) )
	    {
			std::istringstream iss(line);

	    	if (line.find("map:") != string::npos)
	    	{
				string mapHolder;
				iss >> mapHolder >> this->map_path;
			}
	    	else if (line.find("startLocation:") != string::npos)
			{
				int a, b;
				double c;
				string mapHolder;
				iss >> mapHolder >> a >> b >> c;
				this->start.setCol(a);
				this->start.setRow(b);
				this->start.setYaw(c);
			}
	    	else if (line.find("goal:") != string::npos)
	    	{
				int a, b;
				string mapHolder;
				iss >> mapHolder >> a >> b;
				this->goal.setCol(a);
				this->goal.setRow(b);
			}
	    	else if (line.find("robotSize:") != string::npos)
			{
				int a, b;
				string mapHolder;
				iss >> mapHolder >> a >> b;
				this->robot_size_x = a;
				this->robot_size_y = b;
			}
	    	else if (line.find("GridResolutionCM:") != string::npos)
			{
				string mapHolder;
				iss >> mapHolder >> grid_res;
			}
	    	else if (line.find("MapResolutionCM:") != string::npos)
			{
				string mapHolder;
				iss >> mapHolder >> map_res;
			}
	    }
	    myfile.close();
	  }

	  else cout << "File could not open";

	// TODO Auto-generated constructor stub
}

Position RobotParameters::GetStartLocation(){

	return this->start;
}


Point RobotParameters::GetGoalLocation()
{
	return this->goal;
}

string RobotParameters::GetMapPath(){
	return this->map_path.c_str();
}

void RobotParameters::GetRobotSize(int& x, int &y){
	x = this->robot_size_x;
	y = this->robot_size_y;
}

double RobotParameters::GetMapResolution(){
	return this->map_res;
}

int RobotParameters::GetGridResolution(){
	return this->grid_res;
}

RobotParameters::~RobotParameters() {
	// TODO Auto-generated destructor stub
}
