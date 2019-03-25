#include "Demonstration.h"



void demonstration(string fileName)
{
	WorkWwithWorldMap workWwithWorldMap(fileName);

	shared_ptr<GeographicalObject> worldMap = workWwithWorldMap.getWorldMap();
	shared_ptr<GeographicalObject> country;
	shared_ptr<GeographicalObject> city;

	cin.get();
	cin.get();
	cin.get();
}