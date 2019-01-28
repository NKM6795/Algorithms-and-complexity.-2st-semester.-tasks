#pragma once


#include <fstream>
#include "GeographicalObject.h"


class WorkWwithWorldMap
{
	shared_ptr<GeographicalObject> worldMap;

	void getInformationFromTheLine(string &line, string &result, int &position);
	void getInformationFromTheLine(string &line, long &result, int &position);

public:
	WorkWwithWorldMap();
	WorkWwithWorldMap(string name);

	void createWorldMap(string name);

	shared_ptr<GeographicalObject> getWorldMap();
};