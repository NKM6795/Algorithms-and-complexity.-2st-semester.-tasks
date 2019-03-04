#include "Graph.h"
#include "GeographicalObject.h"


Graph::Node::Node() : degree(1)
{

}

Graph::Node::Node(shared_ptr<GeographicalObject> cost) : degree(1), cost(cost)
{
	
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

	shared_ptr<BinomialHeap> newHeap;

	shared_ptr<Node> nodeNewHeap = newHeap->root,
		nodeHeap1 = heap1->root,
		nodeHeap2 = heap2->root;

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
		while (nodeHeap2)
		{
			nodeNewHeap->sibling = nodeHeap2;
			nodeHeap2 = nodeHeap2->sibling;
		}
	}
	else
	{
		while (nodeHeap1)
		{
			nodeNewHeap->sibling = nodeHeap1;
			nodeHeap1 = nodeHeap2->sibling;
		}
	}

	nodeNewHeap = newHeap->root;

	while (nodeNewHeap->sibling)
	{
		if (nodeNewHeap->degree == nodeNewHeap->sibling->degree)
		{

		}
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
	shared_ptr<Node> node = heap->root;
	if (!node)
	{
		return {};
	}

	shared_ptr<GeographicalObject> cost = node->cost;

	while (node->sibling)
	{
		if (node->cost->getAdditionalInformation() > cost->getAdditionalInformation())
		{
			cost = node->cost;
		}
		node = node->sibling;
	}

	return cost;
}