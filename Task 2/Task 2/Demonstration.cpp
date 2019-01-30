#include "Demonstration.h"


void demonstration(string fileName)
{
	WorkWwithWorldMap workWwithWorldMap(fileName);

	long position;
	
	cin >> position;

	shared_ptr<GeographicalObject> worldMap = workWwithWorldMap.getWorldMap();

	shared_ptr<GeographicalObject> country = worldMap->getOwnedObject(position);

	cout << country->getName() << ' ' << country->getAdditionalInformation() << '\n';

	cin >> position;

	shared_ptr<GeographicalObject> city = country->getOwnedObject(position);

	cout << city->getName() << ' ' << city->getAdditionalInformation() << '\n';

	cin.get();
	cin.get();
	cin.get();
}