#pragma once


//#include "GeographicalObject.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;


class GeographicalObject;


class Graph
{
	struct Node
	{
		shared_ptr<GeographicalObject> cost;

		shared_ptr<Node> left,
			right,
			parent;

		Node();
		Node(shared_ptr<GeographicalObject> cost);
		Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent);
		Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent, shared_ptr<Node> left, shared_ptr<Node> right);
	};

	shared_ptr<Node> root;

	void downHeap(vector<shared_ptr<GeographicalObject> > &first, long k, long number);
	void heapSort(vector<shared_ptr<GeographicalObject> > &first);

	void creation(vector<vector<int> > &roots, shared_ptr<Node> parent, int left, int right, vector<shared_ptr<GeographicalObject> > &costs);

public:
	Graph();

	void addVertexes(vector<shared_ptr<GeographicalObject> > &costs);

	shared_ptr<GeographicalObject> getVertex(long information);
};