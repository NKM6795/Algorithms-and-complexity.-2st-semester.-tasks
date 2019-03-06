#include "Graph.h"
#include "GeographicalObject.h"


Graph::Node::Node()
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost) : cost(cost)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent) : cost(cost), parent(parent)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent, shared_ptr<Node> left, shared_ptr<Node> right) : cost(cost), parent(parent), left(left), right(right)
{

}


void Graph::downHeap(vector<shared_ptr<GeographicalObject> > &first, long k, long number)
{
	long child;
	shared_ptr<GeographicalObject> newElement = first[k];

	while (k <= number / 2)
	{
		child = 2 * k;

		if (child < number && first[child]->getAdditionalInformation() < first[child + 1]->getAdditionalInformation())
		{
			++child;
		}
		if (newElement->getAdditionalInformation() >= first[child]->getAdditionalInformation())
		{
			break;
		}

		first[k] = first[child];
		k = child;
	}

	first[k] = newElement;
}

void Graph::heapSort(vector<shared_ptr<GeographicalObject> > &first)
{
	for (int i = int(first.size()) / 2; i >= 0; --i)
	{
		downHeap(first, i, int(first.size()) - 1);
	}

	for (int i = int(first.size()) - 1; i > 0; --i)
	{
		swap(first[i], first[0]);

		downHeap(first, 0, i - 1);
	}
}


void Graph::creation(vector<vector<int> > &roots, shared_ptr<Node> parent, int left, int right, vector<shared_ptr<GeographicalObject> > &costs)
{
	int index = roots[left][right];

	shared_ptr<Node> node = make_shared<Node>(costs[index]);

	if (parent)
	{
		if (parent->cost->getAdditionalInformation() <= node->cost->getAdditionalInformation())
		{
			parent->right = node;
		}
		else
		{
			parent->left = node;
		}
		node->parent = parent;
	}
	else
	{
		root = node;
	}

	if (index - left > 0)
	{
		creation(roots, node, left, index - 1, costs);
	}

	if (right - index > 0)
	{
		creation(roots, node, index + 1, right, costs);
	}
}


void Graph::coutTree(int deep, shared_ptr<Node> node)
{
	if (node->right)
	{
		coutTree(deep + 1, node->right);
	}

	for (int i = 0; i < deep; ++i)
	{
		cout << '\t';
	}
	cout << node->cost->getAdditionalInformation() << '\n';

	if (node->left)
	{
		coutTree(deep + 1, node->left);
	}
}


Graph::Graph()
{

}


void Graph::addVertexes(vector<shared_ptr<GeographicalObject> > &costs)
{
	int number = int(costs.size());

	if (costs.size() == 1)
	{
		costs[0]->setProbability(1.f);
	}
	else
	{
		float sum = 0.f;

		for (int i = 0; i < number - 1; ++i)
		{
			sum += costs[i]->getProbability();
		}

		costs[number - 1]->setProbability(1.f - sum);
	}

	heapSort(costs);

	vector<vector<float> > expectation(number + 2, vector<float>(number + 1, 10000000.f));
	vector<vector<float> > partialSums(number + 2, vector<float>(number + 1));
	vector<vector<int> > roots(number + 1, vector<int>(number + 1, 0));

	for (int i = 0; i < number + 1; ++i)
	{
		expectation[i][i] = 0.f;
		partialSums[i][i] = 0.f;
	}

	for (int l = 1; l <= number; ++l)
	{
		for (int i = 0; i < number - l + 1; ++i)
		{
			int j = i + l;

			partialSums[i][j] = partialSums[i][j - 1] + costs[j-1]->getProbability();

			int left, right;
			if (l == 1)
			{
				left = i;
				right = j;
			}
			else
			{
				left = roots[i][j - 2];
				right = roots[i + 1][j - 1];
			}

			for (int k = left; k <= right; ++k)
			{
				float value = expectation[i][k] + expectation[k + 1][j] + partialSums[i][j];

				if (value < expectation[i][j])
				{
					expectation[i][j] = value;
					roots[i][j - 1] = k;
				}
			}
		}
	}
	
	creation(roots, {}, 0, number - 1, costs);

	cout << "Result: " << expectation[0][number] << '\n';
	cout << "Partial sums:\n";
	for (int i = 0; i <= number; ++i)
	{
		for (int j = 0; j <= number; ++j)
		{
			cout << expectation[i][j] << ' ';
		}
		cout << '\n';
	}
	
	cout << "Partial sums:\n";
	for (int i = 0; i <= number; ++i)
	{
		for (int j = 0; j <= number; ++j)
		{
			cout << partialSums[i][j] << ' ';
		}
		cout << '\n';
	}

	cout << "Roots:\n";
	for (int i = 0; i < number; ++i)
	{
		for (int j = 0; j < number; ++j)
		{
			cout << roots[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << "Tree:\n";
	coutTree();
	cout << "****************\n\n";
}


shared_ptr<GeographicalObject> Graph::getVertex(long information)
{
	shared_ptr<Node> node = root;

	while (true)
	{
		if (node->cost->getAdditionalInformation() == information)
		{
			return node->cost;
		}
		else if (node->cost->getAdditionalInformation() < information)
		{
			if (node->right)
			{
				node = node->right;
			}
			else
			{
				return {};
			}
		}
		else
		{
			if (node->left)
			{
				node = node->left;
			}
			else
			{
				return {};
			}
		}
	}
}


void Graph::coutTree()
{
	coutTree(0, root);
}