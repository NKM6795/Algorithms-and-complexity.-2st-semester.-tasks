#include "Demonstration.h"


void demonstration(string fileName)
{
	WorkWwithWorldMap workWwithWorldMap(fileName);

	long population;
	
	cin >> population;

	shared_ptr<GeographicalObject> worldMap = workWwithWorldMap.getWorldMap();

	shared_ptr<GeographicalObject> country = worldMap->getOwnedObject(population);

	cout << country->getName() << ' ' << country->getAdditionalInformation() << '\n';

	cin >> population;

	shared_ptr<GeographicalObject> city = country->getOwnedObject(population);

	cout << city->getName() << ' ' << city->getAdditionalInformation() << '\n';

	cin.get();
	cin.get();
	cin.get();
}