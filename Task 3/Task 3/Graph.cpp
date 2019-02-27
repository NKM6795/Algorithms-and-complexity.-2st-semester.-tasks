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


void Graph::splay(shared_ptr<Node> node)
{
	if (!node->parent)
	{
		root = node;
	}
	else
	{
		while (true)
		{
			if (node == root)
			{
				return;
			}
			shared_ptr<Node> parent = node->parent;

			if (parent == root)
			{
				zig(node);

				return;
			}

			zigZig(node);

			zigZag(node);
		}
	}
}


void Graph::zig(shared_ptr<Node> node)
{
	if (node == node->parent->left)
	{
		rotateRight(node->parent);
	}
	else
	{
		rotateLeft(node->parent);
	}

	root = node;
}

void Graph::zigZig(shared_ptr<Node> node)
{
	shared_ptr<Node> grandparent = getGrandparent(node);

	if (node->parent && grandparent)
	{
		if (node == node->parent->left && node->parent == grandparent->left)
		{
			rotateRight(grandparent);
			rotateRight(node->parent);

			if (grandparent == root)
			{
				root = node;
			}
		}
		else if (node == node->parent->right && node->parent == grandparent->right)
		{
			rotateLeft(grandparent);
			rotateLeft(node->parent);

			if (grandparent == root)
			{
				root = node;
			}
		}

	}
}

void Graph::zigZag(shared_ptr<Node> node)
{
	shared_ptr<Node> grandparent = getGrandparent(node);

	if (node->parent && grandparent)
	{
		if (node == node->parent->left && node->parent == grandparent->right)
		{
			rotateRight(node->parent);
			rotateLeft(grandparent);

			if (grandparent == root)
			{
				root = node;
			}
		}
		else if (node == node->parent->right && node->parent == grandparent->left)
		{
			rotateLeft(node->parent);
			rotateRight(grandparent);

			if (grandparent == root)
			{
				root = node;
			}
		}
	}
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
		cout << "{||}";
	}
}


Graph::Graph()
{

}


void Graph::addVertex(shared_ptr<GeographicalObject> cost)
{
	shared_ptr<Node> node = make_shared<Node>(cost);
	
	insert(root, node);

	splay(node);
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
	cout << '\n';
	coutTree(root);
	cout << '\n';
}