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
		bool leaf;
		
		int keyNumber;
		vector<long> key;

		shared_ptr<Node> left,
			right,
			parent;

		vector<shared_ptr<Node> > child;

		vector<shared_ptr<GeographicalObject> > cost;

		Node();
		Node(int dimension);
	};

	int dimension;

	shared_ptr<Node> root;


	shared_ptr<Node> getLeaf(long key);

	void split(shared_ptr<Node> node);

	void insert(shared_ptr<GeographicalObject> cost);

	void coutTree(int deep, shared_ptr<Node> node);

public:
	Graph();

	void addVertex(shared_ptr<GeographicalObject> cost);

	shared_ptr<GeographicalObject> getVertex(long information);

	void coutTree();
};