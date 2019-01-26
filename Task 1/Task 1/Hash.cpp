#include "Hash.h"


int getFirstHash(string name, int seed)
{
	int hash = 0;

	for (int i = 0; i < int(name.size()); ++i)
	{
		hash = hash ^ (name[i] * seed);
	}

	return hash;
}

int getSecondHash(string name, int seed)
{
	int hash = 0;

	for (int i = 0; i < int(name.size()); ++i)
	{
		hash = ~(hash ^ ~ (name[i] * seed));
	}

	return hash;
}