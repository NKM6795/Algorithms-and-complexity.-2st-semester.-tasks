#include "WorkWwithWorldMap.h"


WorkWwithWorldMap::WorkWwithWorldMap()
{

}

WorkWwithWorldMap::WorkWwithWorldMap(string name)
{
	createWorldMap(name);
}


void WorkWwithWorldMap::getInformationFromTheLine(string &line, string &result, int &position)
{
	bool canRead = false;

	for (; position < int(line.size()) && line[position] != '}'; ++position)
	{
		if (!canRead && line[position] == '{')
		{
			canRead = true;
		}
		else if (canRead)
		{
			result.push_back(line[position]);
		}
	}

	++position;
}


void WorkWwithWorldMap::createWorldMap(string name)
{
	ifstream fileInput(name);

	vector<shared_ptr<GeographicalObject> > countries;
	vector<shared_ptr<GeographicalObject> > cities;

	string line;
	
	string oldCountry, oldContinent;
	bool firstPass = true;

	while (getline(fileInput, line))
	{
		int i = 0;
		
		string country, continent, city, population;

		getInformationFromTheLine(line, country, i);
		getInformationFromTheLine(line, continent, i);
		getInformationFromTheLine(line, city, i);
		getInformationFromTheLine(line, population, i);


		if (firstPass || oldCountry == country)
		{
			firstPass = false;
		}
		else if (oldCountry != country)
		{
			countries.push_back(shared_ptr<GeographicalObject>(new GeographicalObject(oldCountry, oldContinent, cities)));

			cities.clear();
		}

		oldCountry = country;
		oldContinent = continent;
		
		cities.push_back(shared_ptr<GeographicalObject>(new GeographicalObject(city, population)));
	}

	countries.push_back(shared_ptr<GeographicalObject>(new GeographicalObject(oldCountry, oldContinent, cities)));

	worldMap = shared_ptr<GeographicalObject>(new GeographicalObject("World map", "Megacity list", countries));
}