#include "Graph.h"


bool Graph::dfs(vector<vector<int> > &graph, vector<int> &color, int vertex, int oldVertex)
{
	color[vertex] = 0;

	bool firstOldVertex = true;

	for (int i = 0; i < int(graph[vertex].size()); ++i)
	{
		int currentVertex = graph[vertex][i];
		if (color[currentVertex] == -1)
		{
			if (dfs(graph, color, currentVertex, vertex))
			{
				return true;
			}
		}
		else if (color[currentVertex] == 0)
		{
			if (currentVertex == oldVertex && firstOldVertex)
			{
				firstOldVertex = false;
			}
			else
			{
				return true;
			}
		}
	}

	color[vertex] = 1;
	return false;
}


void Graph::fillingInTheSourceTable(vector<int> &result, vector<vector<pair<int, int> > > &graph, int vertex, int forCheck)
{
	for (int i = 0; i < int(graph[vertex].size()); ++i)
	{
		int currentVertex = graph[vertex][i].first;

		if (result[currentVertex] == forCheck)
		{
			result[currentVertex] = graph[vertex][i].second - result[vertex];

			fillingInTheSourceTable(result, graph, currentVertex, forCheck);
		}
	}
}


pair<int, vector<int> > Graph::getDataToHash(vector<shared_ptr<GeographicalObject> > &objects)
{
	int seed = 6;
	int length = int(objects.size());

	vector<int> firstHash(objects.size()), secondHash(objects.size());

	bool readyToUse = false;
	while (!readyToUse)
	{
		++seed;

		for (int i = 0; i < length; ++i)
		{
			firstHash[i] = getFirstHash(objects[i]->getName(), seed, 20 * length);
			secondHash[i] = getSecondHash(objects[i]->getName(), seed, 20 * length);
		}

		vector<vector<int> > graph(20 * length);
		
		for (int i = 0; i < length; ++i)
		{
			graph[firstHash[i]].push_back(secondHash[i]);
			graph[secondHash[i]].push_back(firstHash[i]);
		}

		vector<int> color(20 * length, -1);

		bool hasACycle = false;

		for (int i = 0; i < 20 * length && !hasACycle; ++i)
		{
			if (color[i] == -1 && graph[i].size() > 0)
			{
				if (dfs(graph, color, i, -1))
				{
					hasACycle = true;
				}
			}
		}

		if (hasACycle)
		{
			graph.clear();
		}
		else
		{
			readyToUse = true;
		}
	}

	vector<vector<pair<int, int> > > graph(20 * length);

	for (int i = 0; i < length; ++i)
	{
		graph[firstHash[i]].push_back({ secondHash[i], i });
		graph[secondHash[i]].push_back({ firstHash[i], i });
	}

	vector<int> result(20 * length, 20 * length);

	for (int i = 0; i < 20 * length; ++i)
	{
		if (result[i] == 20 * length)
		{
			result[i] = 0;

			fillingInTheSourceTable(result, graph, i, 20 * length);
		}
	}

	return { seed, result };
}
