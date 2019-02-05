#include "Demonstration.h"


void demonstration(string fileName)
{
	WorkWwithWorldMap workWwithWorldMap(fileName);

	long information;
	
	cin >> information;

	shared_ptr<GeographicalObject> worldMap = workWwithWorldMap.getWorldMap();

	shared_ptr<GeographicalObject> country = worldMap->getOwnedObject(information);

	if (country)
	{
		cout << country->getName() << ' ' << country->getAdditionalInformation() << '\n';
	}
	else
	{
		cout << "Error\n";

		cin.get();
		cin.get();
		cin.get();

		return;
	}

	cin >> information;

	shared_ptr<GeographicalObject> city = country->getOwnedObject(information);

	if (city)
	{
		cout << city->getName() << ' ' << city->getAdditionalInformation() << '\n';
	}
	else
	{
		cout << "Error\n";
	}

	cin.get();
	cin.get();
	cin.get();
}