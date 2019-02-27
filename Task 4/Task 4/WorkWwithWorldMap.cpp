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

void WorkWwithWorldMap::getInformationFromTheLine(string &line, float &result, int &position)
{
	bool canRead = false;

	bool isInteger = true;
	float divisor = 0.1f;

	for (; position < int(line.size()) && line[position] != '}'; ++position)
	{
		if (!canRead && line[position] == '{')
		{
			canRead = true;
		}
		else if (canRead)
		{
			if (line[position] == '.')
			{
				isInteger = false;
			}
			else
			{
				result = result * 10.f + float(line[position] - '0');
			}

			if (!isInteger)
			{
				divisor *= 10;
			}
		}
	}
	result /= divisor;
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
	float oldCountryProbabilityOfHitting = 0.f, oldCountryIntermediateProbability = 0.f;
	bool firstPass = true;

	while (getline(fileInput, line))
	{
		int i = 0;
		
		string country, city;
		long countryPopulation = 0, cityPopulation = 0;
		float countryProbabilityOfHitting = 0.f, countryIntermediateProbability = 0.f,
			cityProbabilityOfHitting = 0.f, cityIntermediateProbability = 0.f;

		getInformationFromTheLine(line, country, i);
		getInformationFromTheLine(line, countryPopulation, i);
		getInformationFromTheLine(line, countryIntermediateProbability, i);
		getInformationFromTheLine(line, countryProbabilityOfHitting, i);
		getInformationFromTheLine(line, city, i);
		getInformationFromTheLine(line, cityPopulation, i);
		getInformationFromTheLine(line, cityIntermediateProbability, i);
		getInformationFromTheLine(line, cityProbabilityOfHitting, i);


		if (firstPass || oldCountry == country)
		{
			firstPass = false;
		}
		else if (oldCountry != country)
		{
			countries.push_back(shared_ptr<GeographicalObject>(new GeographicalObject(oldCountry, oldCountryPopulation, oldCountryProbabilityOfHitting, oldCountryIntermediateProbability, cities)));

			cities.clear();
		}

		oldCountry = country;
		oldCountryPopulation = countryPopulation;
		
		cities.push_back(shared_ptr<GeographicalObject>(new GeographicalObject(city, cityPopulation, cityProbabilityOfHitting, cityIntermediateProbability)));
	}

	countries.push_back(shared_ptr<GeographicalObject>(new GeographicalObject(oldCountry, oldCountryPopulation, cities)));

	worldMap = shared_ptr<GeographicalObject>(new GeographicalObject("World map", 1, countries));
}


shared_ptr<GeographicalObject> WorkWwithWorldMap::getWorldMap()
{
	return worldMap;
}