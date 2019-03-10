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
			left,
			right,
			parent;

		int degree;

		bool mark;

		Node();
		Node(shared_ptr<GeographicalObject> cost);
	};

	struct FibonacciHeap
	{
		int size;
		shared_ptr<Node> root;

		FibonacciHeap();
		FibonacciHeap(shared_ptr<GeographicalObject> cost);
	};


	shared_ptr<FibonacciHeap> heap;


	void unionLists(shared_ptr<Node> first, shared_ptr<Node> second);

	void merge(shared_ptr<FibonacciHeap> heap);

	void insert(shared_ptr<GeographicalObject> cost);

	void consolidate();

	void coutTree(int deep, shared_ptr<Node> node, shared_ptr<Node> begin);

public:
	Graph();

	void addVertex(shared_ptr<GeographicalObject> cost);

	shared_ptr<GeographicalObject> getMinimum();

	shared_ptr<GeographicalObject> extractMinimum();

	void coutTree();
};