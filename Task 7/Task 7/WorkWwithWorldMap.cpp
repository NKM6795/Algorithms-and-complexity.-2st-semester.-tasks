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

void WorkWwithWorldMap::getInformationFromTheLine(string &line, long &result, int &position)
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
			result = result * 10 + line[position] - '0';
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
	
	string oldCountry;
	long oldCountryPopulation;
	bool firstPass = true;

	while (getline(fileInput, line))
	{
		int i = 0;
		
		string country, city;
		long countryPopulation = 0, cityPopulation = 0;

		getInformationFromTheLine(line, country, i);
		getInformationFromTheLine(line, countryPopulation, i);
		getInformationFromTheLine(line, city, i);
		getInformationFromTheLine(line, cityPopulation, i);


		if (firstPass || oldCountry == country)
		{
			firstPass = false;
		}
		else if (oldCountry != country)
		{
			countries.push_back(shared_ptr<GeographicalObject>(new GeographicalObject(oldCountry, oldCountryPopulation, cities)));

			cities.clear();
		}

		oldCountry = country;
		oldCountryPopulation = countryPopulation;
		
		cities.push_back(shared_ptr<GeographicalObject>(new GeographicalObject(city, cityPopulation)));
	}

	countries.push_back(shared_ptr<GeographicalObject>(new GeographicalObject(oldCountry, oldCountryPopulation, cities)));

	worldMap = shared_ptr<GeographicalObject>(new GeographicalObject("World map", 1, countries));
}


shared_ptr<GeographicalObject> WorkWwithWorldMap::getWorldMap()
{
	return worldMap;
}