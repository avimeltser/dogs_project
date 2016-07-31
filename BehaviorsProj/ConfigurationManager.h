/*
 * ConfigurationManager.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include <map>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

class ConfigurationManager {
public:

	ConfigurationManager();
	static string getMapLocation();
	static void getStartLocation(int& x, int& y, double& yaw);
	static void getGoal(int &x, int &y);
	static void getRobotSize(int& x, int& y);
	static double getMapResolution();
	static int getGridResolution();
	virtual ~ConfigurationManager();
private:
	static map<string, string> _configs;
	static vector<string> split(string str, const char delim);
};

#endif /* CONFIGURATIONMANAGER_H_ */
