#include "Demonstration.h"


void likeUI(shared_ptr<GeographicalObject> &object, shared_ptr<GeographicalObject> parent)
{
	long information;

	cout << "enter something\n";
	cin >> information;

	if (information == -1 || information == -2)
	{
		if (information == -1)
		{
			object = parent->getMinimum();
		}
		else
		{
			object = parent->extractMinimum();
		}

		if (object)
		{
			cout << object->getName() << ' ' << object->getAdditionalInformation() << '\n';
		}
		else
		{
			cout << "Error\n";
		}
	}
	else if (information == -3)
	{
		parent->coutTree();
	}
}


void demonstration(string fileName)
{
	WorkWwithWorldMap workWwithWorldMap(fileName);

	shared_ptr<GeographicalObject> worldMap = workWwithWorldMap.getWorldMap();
	shared_ptr<GeographicalObject> country;
	shared_ptr<GeographicalObject> city;

	while (true)
	{
		cout << "Work with country, ";
		likeUI(country, worldMap);

		if (country)
		{
			cout << "Work with city, ";
			likeUI(city, country);
			country = {};
		}
	}
	cin.get();
	cin.get();
	cin.get();
}