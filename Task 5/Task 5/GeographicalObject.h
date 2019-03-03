#pragma once


#include "Graph.h"
#include <string>
#include <vector>
#include <iostream>


using namespace std;


class Graph;


class GeographicalObject
{
	string name;
	long additionalInformation;

	Graph ownedObjects;
	
public:
	GeographicalObject();
	GeographicalObject(string name, long additionalInformation);
	GeographicalObject(string name, long additionalInformation, vector<shared_ptr<GeographicalObject> > &ownedObjects);

	void setName(string name);
	void setName(string &name);
	string getName();

	void setAdditionalInformation(long additionalInformation);
	void setAdditionalInformation(long &additionalInformation);
	long getAdditionalInformation();

	void setOwnedObjects(vector<shared_ptr<GeographicalObject> > &ownedObjects);

	shared_ptr<GeographicalObject> getOwnedObject(int position);
};