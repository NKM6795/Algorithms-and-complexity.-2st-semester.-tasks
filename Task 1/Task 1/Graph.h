#pragma once


#include "Hash.h"
#include "GeographicalObject.h"
#include <vector>
#include <map>


class GeographicalObject;


class Graph
{
	static bool dfs(vector<vector<int> > &graph, vector<int> &color, int vertex, int oldVertex);
	//Acyclicity test
	//true - has a cycle
	

	static void fillingInTheSourceTable(vector<int> &result, vector<vector<pair<int, int> > > &graph, int vertex, int forCheck);

public:
	static pair<int, vector<int> > getDataToHash(vector<shared_ptr<GeographicalObject> > &objects);
};