#include "Graph.h"
#include "GeographicalObject.h"


Graph::Node::Node() : degree(1)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost) : degree(1), cost(cost)
{
	
}


Graph::BinomialHeap::BinomialHeap()
{
	root = make_shared<Node>();
}

Graph::BinomialHeap::BinomialHeap(shared_ptr<GeographicalObject> cost)
{
	root = make_shared<Node>();
	root->sibling = make_shared<Node>(cost);
}


shared_ptr<Graph::BinomialHeap> Graph::merge(shared_ptr<BinomialHeap> heap1, shared_ptr<BinomialHeap> heap2)
{
	if (!heap1)
	{
		return heap2;
	}
	if (!heap2)
	{
		return heap1;
	}

	shared_ptr<BinomialHeap> newHeap = make_shared<BinomialHeap>();

	shared_ptr<Node> nodeNewHeap = newHeap->root,
		nodeHeap1 = heap1->root->sibling,
		nodeHeap2 = heap2->root->sibling;

	while (nodeHeap1 && nodeHeap2)
	{
		if (nodeHeap1->degree < nodeHeap2->degree)
		{
			nodeNewHeap->sibling = nodeHeap1;
			nodeNewHeap = nodeHeap1;
			nodeHeap1 = nodeHeap1->sibling;
		}
		else
		{
			nodeNewHeap->sibling = nodeHeap2;
			nodeNewHeap = nodeHeap2;
			nodeHeap2 = nodeHeap2->sibling;
		}
	}

	if (!nodeHeap1)
	{
		if (nodeHeap2)
		{
			nodeNewHeap->sibling = nodeHeap2;
		}
	}
	else
	{
		if (nodeHeap1)
		{
			nodeNewHeap->sibling = nodeHeap1;
		}
	}

	shared_ptr<Node> leftSibling;

	bool isChange = true;
	while (isChange)
	{
		nodeNewHeap = newHeap->root->sibling;
		leftSibling = newHeap->root;

		isChange = false;

		while (nodeNewHeap->sibling)
		{
			if (nodeNewHeap->degree == nodeNewHeap->sibling->degree)
			{
				if (nodeNewHeap->cost->getAdditionalInformation() >= nodeNewHeap->sibling->cost->getAdditionalInformation())
				{
					nodeNewHeap->parent = nodeNewHeap->sibling;
					shared_ptr<Node> temp = nodeNewHeap->sibling;
					nodeNewHeap->sibling = nodeNewHeap->sibling->child;
					temp->child = nodeNewHeap;
					++temp->degree;
					leftSibling->sibling = temp;

					nodeNewHeap = temp;
				}
				else
				{
					shared_ptr<Node> temp = nodeNewHeap->sibling;
					nodeNewHeap->sibling = temp->sibling;
					temp->parent = nodeNewHeap;
					temp->sibling = nodeNewHeap->child;
					nodeNewHeap->child = temp;
					++nodeNewHeap->degree;
				}
				isChange = true;
			}
			if (nodeNewHeap->sibling)
			{
				leftSibling = nodeNewHeap;
				nodeNewHeap = nodeNewHeap->sibling;
			}
		}
	}
	return newHeap;
}


void Graph::insert(shared_ptr<GeographicalObject> cost)
{
	shared_ptr<BinomialHeap> tempHeap = make_shared<BinomialHeap>(cost);

	heap = merge(heap, tempHeap);
}


void Graph::coutTree(int deep, shared_ptr<Node> node)
{
	for (int i = 0; i < deep; ++i)
	{
		cout << '\t';
	}

	cout << node->cost->getAdditionalInformation() << '\n';
	
	if (node->child)
	{
		coutTree(deep + 1, node->child);
	}

	if (node->sibling)
	{
		coutTree(deep, node->sibling);
	}
}


Graph::Graph()
{

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

	shared_ptr<Node> node = heap->root->sibling;

	shared_ptr<GeographicalObject> cost = node->cost;

	while (node)
	{
		if (node->cost->getAdditionalInformation() < cost->getAdditionalInformation())
		{
			cost = node->cost;
		}
		node = node->sibling;
	}

	return cost;
}

shared_ptr<GeographicalObject> Graph::extractMinimum()
{
	if (!heap)
	{
		return {};
	}

	shared_ptr<Node> node = heap->root;

	shared_ptr<Node> minNode = node->sibling,
		leftSiblingMinNode = heap->root;

	while (node->sibling)
	{
		if (node->sibling->cost->getAdditionalInformation() < minNode->cost->getAdditionalInformation())
		{
			minNode = node->sibling;
			leftSiblingMinNode = node;
		}
		node = node->sibling;
	}

	leftSiblingMinNode->sibling = minNode->sibling;

	if (!heap->root->sibling)
	{
		heap.reset();
	}

	if (minNode->child)
	{
		shared_ptr<BinomialHeap> newHeap = make_shared<BinomialHeap>();

		newHeap->root->sibling = minNode->child;
		node = minNode->child->sibling;
		minNode->child->sibling = {};

		while (node)
		{
			shared_ptr<Node> temp = node->sibling;

			node->sibling = newHeap->root->sibling;
			newHeap->root->sibling = node;
			node = temp;
		}

		heap = merge(heap, newHeap);
	}

	return minNode->cost;
}


void Graph::coutTree()
{
	if (heap)
	{
		coutTree(0, heap->root->sibling);
	}
	else
	{
		cout << "Nothing\n";
	}
}