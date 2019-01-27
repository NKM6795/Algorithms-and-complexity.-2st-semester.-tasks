#pragma once


#include "Hash.h"
#include "GeographicalObject.h"
#include <vector>
#include <map>


class GeographicalObject;


class Graph
{

public:
	static pair<int, pair<vector<map<int, int> >, vector<map<int, int> > > > getDataToHash(vector<shared_ptr<GeographicalObject> > &objects);
};