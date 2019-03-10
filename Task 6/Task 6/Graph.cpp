#include "Graph.h"
#include "GeographicalObject.h"


Graph::Node::Node()
{
	leaf = false;
	keyNumber = 0;
}

Graph::Node::Node(int dimension)
{
	leaf = false;
	keyNumber = 0;
	key.resize(2 * dimension);
	cost.resize(2 * dimension);
	child.resize(10000);
}


shared_ptr<Graph::Node> Graph::getLeaf(long key)
{
	shared_ptr<Node> node = root;

	while (!node->leaf)
	{
		for (int i = 0; i <= node->keyNumber; ++i)
		{
			if (i == node->keyNumber || key < node->key[i])
			{
				node = node->child[i];
				break;
			}
		}
	}

	return node;
}


void Graph::split(shared_ptr<Node> node)
{
	shared_ptr<Node> newNode = make_shared<Node>(dimension);

	if (node->right)
	{
		newNode->right = node->right;
		node->right->left = newNode;
	}

	node->right = newNode;
	newNode->left = node;

	
	long middleKey = node->key[dimension];
	newNode->keyNumber = dimension - 1;
	node->keyNumber = dimension;

	for (int i = 0; i <= newNode->keyNumber - 1; ++i)
	{
		newNode->key[i] = node->key[i + dimension + 1];
		newNode->cost[i] = node->cost[i + dimension + 1];
		newNode->child[i] = node->child[i + dimension + 1];
		if (newNode->child[i])
		{
			newNode->child[i]->parent = newNode;
		}
	}

	newNode->child[newNode->keyNumber] = node->child[2 * dimension];
	if (newNode->child[newNode->keyNumber])
	{
		newNode->child[newNode->keyNumber]->parent = newNode;
	}

	if (node->leaf)
	{
		++newNode->keyNumber;
		newNode->leaf = true;

		for (int i = newNode->keyNumber - 1; i > 0; --i)
		{
			newNode->key[i] = newNode->key[i - 1];
			newNode->cost[i] = newNode->cost[i - 1];
		}
		newNode->key[0] = node->key[dimension];
		newNode->cost[0] = node->cost[dimension];
	}

	if (node == root)
	{
		root = make_shared<Node>(dimension);
		root->key[0] = middleKey;
		root->child[0] = node;
		root->child[1] = newNode;
		root->keyNumber = 1;
		node->parent = root;
		newNode->parent = root;
	}
	else
	{
		newNode->parent = node->parent;
		shared_ptr<Node> parent = node->parent;

		int position = 0;

		while (position < parent->keyNumber && parent->key[position] < middleKey)
		{
			++position;
		}

		for (int i = parent->keyNumber; i > position; --i)
		{
			parent->key[i] = parent->key[i - 1];
		}
		for (int i = parent->keyNumber + 1; i > position + 1; --i)
		{
			parent->child[i] = parent->child[i - 1];
		}

		parent->key[position] = middleKey;
		parent->child[position + 1] = newNode;

		++parent->keyNumber;

		if (parent->keyNumber == 2 * dimension)
		{
			split(parent);
		}
	}
}


void Graph::insert(shared_ptr<GeographicalObject> cost)
{
	if (!root)
	{
		root = make_shared<Node>(dimension);
		root->leaf = true;
	}

	long key = cost->getAdditionalInformation();

	shared_ptr<Node> leaf = getLeaf(key);

	int position = 0;

	while (position < leaf->keyNumber && leaf->key[position] < key)
	{
		++position;
	}
	
	for (int i = leaf->keyNumber; i > position; --i)
	{
		leaf->key[i] = leaf->key[i - 1];
		leaf->cost[i] = leaf->cost[i - 1];
	}

	leaf->key[position] = key;
	leaf->cost[position] = cost;

	++leaf->keyNumber;

	if (leaf->keyNumber == 2 * dimension)
	{
		split(leaf);
	}
}


void Graph::coutTree(int deep, shared_ptr<Node> node)
{
	for (int i = 0; i < deep; ++i)
	{
		cout << '\t';
	}
	
	cout << "{ ";
	for (int i = 0; i < node->keyNumber; ++i)
	{
		cout << node->key[i] << ' ';
	}
	cout << "}\n";
	

	bool needMargin = false;
	for (int i = 0; i <= node->keyNumber; ++i)
	{
		if (node->child[i])
		{
			coutTree(deep + 1, node->child[i]);
			needMargin = true;
		}
	}
	if (needMargin)
	{
		cout << '\n';
	}
}


Graph::Graph()
{
	dimension = 5;
}


void Graph::addVertex(shared_ptr<GeographicalObject> cost)
{
	insert(cost);
}


shared_ptr<GeographicalObject> Graph::getVertex(long information)
{
	shared_ptr<Node> node = getLeaf(information);

	int oldI = 0;
	for (int i = 0; i < node->keyNumber && node->key[i] <= information; ++i)
	{
		if (information == node->key[i])
		{
			return node->cost[i];
		}
		oldI = i;
	}

	if (oldI + 1 < node->keyNumber && abs(node->cost[oldI]->getAdditionalInformation() - information) > abs(node->cost[oldI + 1]->getAdditionalInformation() - information))
	{
		return node->cost[oldI + 1];
	}
	else
	{
		if (node->right && abs(node->cost[oldI]->getAdditionalInformation() - information) > abs(node->right->cost[0]->getAdditionalInformation() - information))
		{
			return node->right->cost[0];
		}
		else
		{
			return node->cost[oldI];
		}
	}

	return {};
}


void Graph::coutTree()
{
	coutTree(0, root);
}