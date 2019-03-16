#include "Graph.h"
#include "GeographicalObject.h"


Graph::Node::Node() : degree(0)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost) : degree(0), cost(cost)
{
	
}


Graph::FibonacciHeap::FibonacciHeap()
{
	size = 0;
}

Graph::FibonacciHeap::FibonacciHeap(shared_ptr<GeographicalObject> cost)
{
	size = 0;
	root = make_shared<Node>(cost);
}


void Graph::unionLists(shared_ptr<Node> first, shared_ptr<Node> second)
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


void Graph::merge(shared_ptr<FibonacciHeap> heap)
{
	if (heap->size == 0)
	{
		return;
	}
	if (this->heap->size == 0)
	{
		this->heap->root = heap->root;
		this->heap->size = heap->size;
	}
	else
	{
		unionLists(this->heap->root, heap->root);
		this->heap->size += heap->size;

		if (heap->root->cost->getAdditionalInformation() < this->heap->root->cost->getAdditionalInformation())
		{
			this->heap->root = heap->root;
		}
	}
}


void Graph::insert(shared_ptr<GeographicalObject> cost)
{
	shared_ptr<Node> newNode = make_shared<Node>(cost);

	if (heap->size == 0)
	{
		heap->root = newNode;
		heap->root->left = newNode;
		heap->root->right = newNode;
	}
	else
	{
		heap->root->right->left = newNode;
		newNode->right = heap->root->right;
		heap->root->right = newNode;
		newNode->left = heap->root;
	}

	if (newNode->cost->getAdditionalInformation() < heap->root->cost->getAdditionalInformation())
	{
		heap->root = newNode;
	}
	++heap->size;
}


void Graph::consolidate()
{
	vector<shared_ptr<Node> > roots(heap->size);
	roots[heap->root->degree] = heap->root;

	shared_ptr<Node> node = heap->root->right;
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
			shared_ptr<Node> addTo, adding;
			if (conflict->cost->getAdditionalInformation() < node->cost->getAdditionalInformation())
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

		if (heap->root->cost->getAdditionalInformation() > node->cost->getAdditionalInformation())
		{
			heap->root = node;
		}
	}
}


void Graph::coutTree(int deep, shared_ptr<Node> node, shared_ptr<Node> begin)
{
	for (int i = 0; i < deep; ++i)
	{
		cout << '\t';
	}

	cout << node->cost->getAdditionalInformation() << ' ' << node->degree << '\n';
	
	if (node->child)
	{
		coutTree(deep + 1, node->child, node->child->left);
	}

	if (node != begin)
	{
		coutTree(deep, node->right, begin);
	}
}


Graph::Graph()
{
	heap = make_shared<FibonacciHeap>();
}


void Graph::addVertex(shared_ptr<GeographicalObject> cost)
{
	insert(cost);
}


shared_ptr<GeographicalObject> Graph::getMinimum()
{	
	if (!heap)
	{
		return {};
	}

	return heap->root->cost;
}

shared_ptr<GeographicalObject> Graph::extractMinimum()
{
	if (heap->size == 0)
	{
		return {};
	}

	shared_ptr<Node> previousMin = heap->root;

	unionLists(heap->root, heap->root->child);

	heap->root->left->right = heap->root->right;
	heap->root->right->left = heap->root->left;

	if (previousMin->right == previousMin)
	{
		heap->root = {};
		--heap->size;
		return previousMin->cost;
	}

	heap->root = heap->root->right;

	consolidate();
	
	--heap->size;
	return previousMin->cost;
}


void Graph::coutTree()
{
	if (heap)
	{
		coutTree(0, heap->root, heap->root->left);
	}
	else
	{
		cout << "Nothing\n";
	}
}