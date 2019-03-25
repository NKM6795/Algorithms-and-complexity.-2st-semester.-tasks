#include "Graph.h"
#include "GeographicalObject.h"
#include <fstream>
#include <algorithm>



Graph::FibonacciHeap::Node::Node() : degree(0)
{

}

Graph::FibonacciHeap::Node::Node(pair<int, int> cost) : degree(0), cost(cost)
{

}


Graph::FibonacciHeap::FibonacciHeap()
{
	size = 0;
}

Graph::FibonacciHeap::FibonacciHeap(pair<int, int> cost)
{
	size = 1;
	root = make_shared<Node>(cost);
	root->left = root;
	root->right = root;
}


bool Graph::FibonacciHeap::empty()
{
	return !size;
}


void Graph::FibonacciHeap::unionLists(shared_ptr<Node> first, shared_ptr<Node> second)
{
	if (!first || !second)
	{
		return;
	}
	shared_ptr<Node> left = first->left,
		right = second->right;

	second->right = first;
	first->left = second;

	left->right = right;
	right->left = left;
}


void Graph::FibonacciHeap::insert(pair<int, int> cost)
{
	shared_ptr<Node> newNode = make_shared<Node>(cost);

	if (size == 0)
	{
		root = newNode;
		root->left = newNode;
		root->right = newNode;
	}
	else
	{
		root->right->left = newNode;
		newNode->right = root->right;
		root->right = newNode;
		newNode->left = root;
	}

	if (cost < root->cost)
	{
		root = newNode;
	}
	++size;
}


void Graph::FibonacciHeap::consolidate()
{
	vector<shared_ptr<Node> > roots(size);
	roots[root->degree] = root;

	shared_ptr<Node> node = root->right;
	while (roots[node->degree] != node)
	{
		if (!roots[node->degree] || roots[node->degree]->degree != node->degree || roots[node->degree]->parent)
		{
			roots[node->degree] = node;
			node = node->right;
		}
		else
		{
			shared_ptr<Node> conflict = roots[node->degree];
			roots[node->degree] = {};

			shared_ptr<Node> addTo, adding;
			if (conflict->cost < node->cost)
			{
				addTo = conflict;
				adding = node;
			}
			else
			{
				addTo = node;
				adding = conflict;
			}

			adding->left->right = adding->right;
			adding->right->left = adding->left;

			adding->parent = addTo;
			if (!addTo->child)
			{
				addTo->child = adding;
				adding->left = adding;
				adding->right = adding;
			}
			else
			{
				adding->right = addTo->child->right;
				adding->left = addTo->child;
				addTo->child->right->left = adding;
				addTo->child->right = adding;
			}
			++addTo->degree;
			node = addTo;
		}

		if (root->cost > node->cost)
		{
			root = node;
		}
	}
}


pair<int, int> Graph::FibonacciHeap::getMinimum()
{
	if (!root)
	{
		return {};
	}

	return root->cost;
}


pair<int, int> Graph::FibonacciHeap::extractMinimum()
{
	if (size == 0)
	{
		return {};
	}

	shared_ptr<Node> previousMin = root;

	unionLists(root, root->child);

	if (root->child)
	{
		root->child->parent = {};
	}

	root->left->right = root->right;
	root->right->left = root->left;

	if (previousMin->right == previousMin)
	{
		root = {};
		--size;
		return previousMin->cost;
	}

	root = root->right;

	consolidate();
	
	--size;
	return previousMin->cost;
}


void Graph::FibonacciHeap::coutTree(int deep, shared_ptr<Node> node, shared_ptr<Node> begin)
{
	for (int i = 0; i < deep; ++i)
	{
		cout << '\t';
	}

	cout << node->cost.first << '|' << node->cost.second << ' ' << node->degree << '\n';

	if (node->child)
	{
		coutTree(deep + 1, node->child, node->child->left);
	}

	if (node != begin)
	{
		coutTree(deep, node->right, begin);
	}
}

void Graph::FibonacciHeap::coutTree()
{
	if (root)
	{
		coutTree(0, root, root->left);
		cout << "*****\n";
	}
	else
	{
		cout << "Nothing\n";
	}
}


void Graph::getLinks()
{
	srand(4);

	number = int(costs.size());

	graph.clear();
	graph.resize(number);

	if (number == 1)
	{
		return;
	}

	vector<int> indexes(number);

	for (int i = 0; i < number; ++i)
	{
		indexes[i] = i;
	}

	for (int i = 0; i < number; ++i)
	{
		int vertexCount = rand() % ((number) / 2);

		random_shuffle(indexes.begin(), indexes.end());

		for (int j = 0; j < vertexCount; ++j)
		{
			if (indexes[j] != i)
			{
				graph[i].push_back({ indexes[j], costs[i]->getAdditionalInformation() - costs[indexes[j]]->getAdditionalInformation() + rand() % 10 });
			}
		}
	}
}


vector<vector<int> > Graph::johnson(vector<vector<pair<int, int> > > &graph)
{
	vector<vector<int> > weights(number + 1, vector<int>(number + 1, 1000000009));

	for (int i = 0; i < int(graph.size()); ++i)
	{
		for (int j = 0; j < int(graph[i].size()); ++j)
		{
			weights[i][graph[i][j].first] = graph[i][j].second;
		}
	}

	coutMatrix(weights);

	int newVertex = number;

	graph.push_back({});
	for (int i = 0; i < number; ++i)
	{
		graph[newVertex].push_back({ i, 0 });
		weights[newVertex][i] = 0;
	}

	vector<int> adjustment;

	if (!bellmanFord(graph, newVertex, weights, adjustment))
	{
		cout << "The input graph has a negative weight cycle\n";
		return {};
	}
	else
	{
		vector<vector<int> > newWeights(number + 1, vector<int>(number + 1, 1000000009));

		for (int i = 0; i < int(graph.size()); ++i)
		{
			for (int j = 0; j < int(graph[i].size()); ++j)
			{
				newWeights[i][graph[i][j].first] = weights[i][graph[i][j].first] + adjustment[i] - adjustment[graph[i][j].first];
			}
		}

		graph.pop_back();

		vector<vector<int> > result(number + 1, vector<int>(number + 1, 1000000009));

		vector<int> distance;

		for (int i = 0; i < int(graph.size()); ++i)
		{
			dijkstra(graph, i, newWeights, distance);

			for (int j = 0; j < int(graph[i].size()); ++j)
			{
				result[i][graph[i][j].first] = distance[graph[i][j].first] + adjustment[graph[i][j].first] - adjustment[i];
			}
		}

		return result;
	}
}


bool Graph::bellmanFord(vector<vector<pair<int, int> > > &graph, int vertex, vector<vector<int> > &weights, vector<int> &distance)
{
	distance.clear();
	distance.resize(graph.size(), 1000000009);
	distance[vertex] = 0;

	for (int k = 1; k < int(graph.size()) - 1; ++k)
	{
		for (int i = 0; i < int(graph.size()); ++i)
		{
			for (int j = 0; j < int(graph[i].size()); ++j)
			{
				if (distance[graph[i][j].first] > distance[i] + weights[i][graph[i][j].first])
				{
					distance[graph[i][j].first] = distance[i] + weights[i][graph[i][j].first];
				}
			}
		}
	}

	for (int i = 0; i < int(graph.size()); ++i)
	{
		for (int j = 0; j < int(graph[i].size()); ++j)
		{
			if (distance[graph[i][j].first] > distance[i] + weights[i][graph[i][j].first])
			{
				return false;
			}
		}
	}

	return true;
}


void Graph::dijkstra(vector<vector<pair<int, int> > > &graph, int vertex, vector<vector<int> > &weights, vector<int> &distance)
{
	distance.clear();
	distance.resize(graph.size(), 1000000009);
	distance[vertex] = 0;

	FibonacciHeap priorityQueue;

	priorityQueue.insert({ 0, vertex });

	while (!priorityQueue.empty())
	{
		int u = priorityQueue.extractMinimum().second;

		for (int i = 0; i < int(graph[u].size()); ++i)
		{
			if (distance[graph[u][i].first] > distance[u] + weights[u][graph[u][i].first])
			{
				distance[graph[u][i].first] = distance[u] + weights[u][graph[u][i].first];
				priorityQueue.insert({ distance[graph[u][i].first], graph[u][i].first });
			}
		}
	}
}


void Graph::coutMatrix(vector<vector<int> > &weights)
{
	cout.width(9);
	cout << ' ';
	for (int i = 0; i < int(weights.size()) - 1; ++i)
	{
		cout.width(9);
		cout << i;
	}
	cout << '\n';

	for (int i = 0; i < int(weights.size()) - 1; ++i)
	{
		cout.width(9);
		cout << i;
		for (int j = 0; j < int(weights.size()) - 1; ++j)
		{
			if (weights[i][j] == 1000000009)
			{
				cout.width(9);
				cout << "INF";
			}
			else
			{
				cout.width(9);
				cout << weights[i][j];
			}
		}
		cout << '\n';
	}
	cout << "**********\n";
}


Graph::Graph()
{

}


void Graph::addVertexes(vector<shared_ptr<GeographicalObject> > costs)
{
	this->costs = costs;
	getLinks();
	coutGraph();

	vector<vector<int> > distance = johnson(graph);

	coutMatrix(distance);
}


void Graph::coutGraph()
{
	ofstream fileOut("Matrix.dat");

	fileOut << "GraphPlot[{";

	bool first = true;

	for (int i = 0; i < int(graph.size()); ++i)
	{
		for (int j = 0; j < int(graph[i].size()); ++j)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				fileOut << ",";
			}
			fileOut << "{" << "\"" << i << "," << costs[i]->getAdditionalInformation() << "\" -> \"" << graph[i][j].first << "," << costs[graph[i][j].first]->getAdditionalInformation() << "\", \"" << graph[i][j].second << "\"}";
		}
	}

	fileOut << "}, VertexLabeling->True, DirectedEdges -> True]\n";

	fileOut.close();
}