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

		shared_ptr<Node> child,
			sibling,
			parent;

		int degree;

		Node();
		Node(shared_ptr<GeographicalObject> cost);
	};

	struct BinomialHeap
	{
		shared_ptr<Node> root;

		BinomialHeap();
		BinomialHeap(shared_ptr<GeographicalObject> cost);
	};


	shared_ptr<BinomialHeap> heap;


	shared_ptr<BinomialHeap> merge(shared_ptr<BinomialHeap> heap1, shared_ptr<BinomialHeap> heap2);

	void insert(shared_ptr<GeographicalObject> cost);

	void coutTree(int deep, shared_ptr<Node> node);

public:
	Graph();

	void addVertex(shared_ptr<GeographicalObject> cost);

	shared_ptr<GeographicalObject> getMinimum();

	shared_ptr<GeographicalObject> extractMinimum();

	void coutTree();
};