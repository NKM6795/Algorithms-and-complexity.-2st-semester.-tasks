#pragma once


//#include "GeographicalObject.h"
#include <string>
#include <vector>
#include <iostream>


using namespace std;


class GeographicalObject;


class Graph
{
	struct Node
	{
		shared_ptr<GeographicalObject> cost;

		shared_ptr<Node> left,
			sibling,
			parent;

		int degree;

		Node();
		Node(shared_ptr<GeographicalObject> cost);
	};

	struct BinomialHeap
	{
		shared_ptr<Node> root;
	};


	shared_ptr<BinomialHeap> heap;


	shared_ptr<BinomialHeap> merge(shared_ptr<BinomialHeap> heap1, shared_ptr<BinomialHeap> heap2);
	
public:
	Graph();

	void addVertex(shared_ptr<GeographicalObject> cost);

	shared_ptr<GeographicalObject> getVertex(long information);
};