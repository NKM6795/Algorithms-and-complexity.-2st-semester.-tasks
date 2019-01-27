#include "Graph.h"


pair<int, pair<vector<map<int, int> >, vector<map<int, int> > > > Graph::getDataToHash(vector<shared_ptr<GeographicalObject> > &objects)
{
	int seed = 7;
	int length = int(objects.size());

	vector<int> firstHash(objects.size()), secondHash(objects.size());

	for (int i = 0; i < length; ++i)
	{
		firstHash[i] = getFirstHash(objects[i]->getName(), seed, length);
		secondHash[i] = getSecondHash(objects[i]->getName(), seed, length);
	}

	return { seed, { {}, {} } };
}
