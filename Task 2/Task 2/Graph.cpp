#include "Graph.h"
#include "GeographicalObject.h"


Graph::Node::Node() : color(false), dimension(1)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost) : color(false), dimension(1), cost(cost)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent) : color(false), dimension(1), cost(cost), parent(parent)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent, shared_ptr<Node> left, shared_ptr<Node> right) : color(false), dimension(1), cost(cost), parent(parent), left(left), right(right)
{

}


void Graph::insert(shared_ptr<Node> parent, shared_ptr<Node> node)
{
	while (parent)
	{
		if (node->cost->getAdditionalInformation() >= parent->cost->getAdditionalInformation())
		{
			if (parent->right)
			{
				parent = parent->right;
			}
			else
			{
				node->parent = parent;
				parent->right = node;
				return;
			}
		}
		else
		{
			if (parent->left)
			{
				parent = parent->left;
			}
			else
			{
				node->parent = parent;
				parent->left = node;
				return;
			}
		}
	}
}


void Graph::smallRecount(shared_ptr<Node> node)
{
	shared_ptr<Node> current = node;

	while (current->parent)
	{
		current = current->parent;
		++current->dimension;
	}
}


shared_ptr<Graph::Node> Graph::getGrandparent(shared_ptr<Node> node)
{
	if (node->parent && node->parent->parent)
	{
		return node->parent->parent;
	}
	else
	{
		return {};
	}
}

shared_ptr<Graph::Node> Graph::getUncle(shared_ptr<Node> node)
{
	if (node->parent && node->parent->parent)
	{
		if (node->parent->parent->left && node->parent->parent->left == node->parent)
		{
			return node->parent->parent->right;
		}
		else
		{
			return node->parent->parent->left;
		}
	}
	else
	{
		return {};
	}
}


void Graph::rotateLeft(shared_ptr<Node> node)
{
	shared_ptr<Node> current = node->right;

	//Recount
	{
		int tempDimention = node->dimension;

		if (current->right)
		{
			node->dimension -= current->right->dimension;
		}
		node->dimension -= 1;

		current->dimension = tempDimention;
	}

	current->parent = node->parent;
	if (node->parent)
	{
		if (node->parent->left == node)
		{
			node->parent->left = current;
		}
		else
		{
			node->parent->right = current;
		}
	}
	else
	{
		root = current;
	}

	node->right = current->left;
	if (current->left)
	{
		current->left->parent = node;
	}

	node->parent = current;
	current->left = node;
}

void Graph::rotateRight(shared_ptr<Node> node)
{
	shared_ptr<Node> current = node->left;

	//Recount
	{
		int tempDimention = node->dimension;

		if (current->left)
		{
			node->dimension -= current->left->dimension;
		}
		node->dimension -= 1;

		current->dimension = tempDimention;
	}

	current->parent = node->parent;
	if (node->parent)
	{
		if (node->parent->left == node)
		{
			node->parent->left = current;
		}
		else
		{
			node->parent->right = current;
		}
	}
	else
	{
		root = current;
	}

	node->left = current->right;
	if (current->right)
	{
		current->right->parent = node;
	}

	node->parent = current;
	current->right = node;
}


void Graph::variant1(shared_ptr<Node> node)
{
	if (!node->parent)
	{
		root = node;
		root->color = true;
	}
	else
	{
		variant2(node);
	}
}

void Graph::variant2(shared_ptr<Node> node)
{
	if (node->parent->color)
	{
		return;
	}
	else
	{
		variant3(node);
	}
}

void Graph::variant3(shared_ptr<Node> node)
{
	shared_ptr<Node> uncle = getUncle(node),
		grandparent = getGrandparent(node);

	if (uncle && !uncle->color)
	{
		node->parent->color = true;
		uncle->color = true;

		grandparent->color = false;
		variant1(grandparent);
	}
	else
	{
		variant4(node);
	}
}

void Graph::variant4(shared_ptr<Node> node)
{
	shared_ptr<Node> grandparent = getGrandparent(node);

	if (node == node->parent->right && node->parent == grandparent->left)
	{
		rotateLeft(node->parent);

		node = node->left;
	}
	else if (node == node->parent->left && node->parent == grandparent->right)
	{
		rotateRight(node->parent);

		node = node->right;
	}

	variant5(node);
}

void Graph::variant5(shared_ptr<Node> node)
{
	shared_ptr<Node> grandparent = getGrandparent(node);

	node->parent->color = true;
	grandparent->color = false;

	if (node == node->parent->left && node->parent == grandparent->left)
	{
		rotateRight(grandparent);
	}
	else
	{
		rotateLeft(grandparent);
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
	cout << node->cost->getAdditionalInformation() << " {" << 1 * node->color << "}\n";

	if (node->left)
	{
		coutTree(deep + 1, node->left);
	}
}

Graph::Graph()
{

}


void Graph::addVertex(shared_ptr<GeographicalObject> cost)
{
	shared_ptr<Node> node = make_shared<Node>(cost);
	
	insert(root, node);

	smallRecount(node);

	variant1(node);
}


void Graph::coutTree()
{
	coutTree(0, root);
}
