#include "Demonstration.h"


void demonstration(string fileName)
{
	WorkWwithWorldMap workWwithWorldMap(fileName);

	string name;
	
	getline(cin, name);

	shared_ptr<GeographicalObject> worldMap = workWwithWorldMap.getWorldMap();

	shared_ptr<GeographicalObject> country = worldMap->getOwnedObject(name);

	cout << country->getName() << ' ' << country->getAdditionalInformation() << '\n';

	getline(cin, name);

	shared_ptr<GeographicalObject> city = country->getOwnedObject(name);

	cout << city->getName() << ' ' << city->getAdditionalInformation() << '\n';

	cin.get();
	cin.get();
	cin.get();
}