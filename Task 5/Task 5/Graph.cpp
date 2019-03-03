#include "Graph.h"
#include "GeographicalObject.h"


Graph::Node::Node() : color(false)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost) : color(false), cost(cost)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent) : color(false), cost(cost), parent(parent)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent, shared_ptr<Node> left, shared_ptr<Node> right) : color(false), cost(cost), parent(parent), left(left), right(right)
{

}

Graph::Node::Node(shared_ptr<Node> node)
{
	this->color = node->color;
	this->cost = node->cost;
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


void Graph::makeVersion(shared_ptr<Node> root, shared_ptr<Node> node)
{
	if (node == root)
	{
		return;
	}
	shared_ptr<Node> parent = node->parent;

	shared_ptr<Node> newParent = make_shared<Node>(parent);

	{
		if (parent->left)
		{
			parent->left->parent = newParent;
			newParent->left = parent->left;
		}
		if (parent->right)
		{
			parent->right->parent = newParent;
			newParent->right = parent->right;
		}
	
		if (node == parent->left)
		{
			parent->left = {};
		}
		else if (node == parent->right)
		{
			parent->right = {};
		}
	}

	while (parent != root)
	{
		shared_ptr<Node> grandparent = parent->parent;
		shared_ptr<Node> newGrandparent = make_shared<Node>(grandparent);
		
		if (grandparent->left == parent)
		{
			newGrandparent->left = newParent;
			
			if (grandparent->right)
			{
				newGrandparent->right = grandparent->right;
				newGrandparent->right->parent = newGrandparent;
			}
		}
		else
		{
			newGrandparent->right = newParent;

			if (grandparent->left)
			{
				newGrandparent->left = grandparent->left;
				newGrandparent->left->parent = newGrandparent;
			}
		}
		newParent->parent = newGrandparent;

		parent = parent->parent;
		newParent = newParent->parent;
	}

	this->root = newParent;
	return;
}


void Graph::coutTree(shared_ptr<Node> node)
{
	if (node)
	{
		cout << "{ ";
		coutTree(node->left);

		cout << " | ";
		cout << node->cost->getAdditionalInformation() << " | ";

		coutTree(node->right);
		cout << " }";
	}
	else
	{
		cout << "{}";
	}
}


Graph::Graph()
{

}


void Graph::addVertex(shared_ptr<GeographicalObject> cost)
{
	shared_ptr<Node> node = make_shared<Node>(cost);
	
	insert(root, node);

	if (!node->parent)
	{
		root = node;
		root->color = true;
	}
	//variant1(node);

	makeVersion(root, node);

	versions.push_back(root);
}


shared_ptr<GeographicalObject> Graph::getVertex(long information)
{
	return getVertex(information, int(versions.size()) - 1);
}

shared_ptr<GeographicalObject> Graph::getVertex(long information, int version)
{
	if (version < 0 || version >= int(versions.size()))
	{
		return {};
	}

	shared_ptr<Node> node = versions[version];

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
	coutTree(int(versions.size()) - 1);
}

void Graph::coutTree(int version)
{
	if (version < 0 || version >= int(versions.size()))
	{
		return;
	}

	cout << '\n';
	coutTree(versions[version]);
	cout << '\n';
}