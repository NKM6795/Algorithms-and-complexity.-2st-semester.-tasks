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
		
		//true - black
		//false - red
		bool color;

		shared_ptr<Node> left,
			right,
			parent;

		Node();
		Node(shared_ptr<GeographicalObject> cost);
		Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent);
		Node(shared_ptr<GeographicalObject> cost, shared_ptr<Node> parent, shared_ptr<Node> left, shared_ptr<Node> right);
		Node(shared_ptr<Node> node);
	};

	vector<shared_ptr<Node> > versions;

	shared_ptr<Node> root;


	void insert(shared_ptr<Node> parent, shared_ptr<Node> node);

	shared_ptr<Node> getGrandparent(shared_ptr<Node> node);
	shared_ptr<Node> getUncle(shared_ptr<Node> node);

	void rotateLeft(shared_ptr<Node> node);
	void rotateRight(shared_ptr<Node> node);

	void variant1(shared_ptr<Node> node);
	void variant2(shared_ptr<Node> node);
	void variant3(shared_ptr<Node> node);
	void variant4(shared_ptr<Node> node);
	void variant5(shared_ptr<Node> node);

	void makeVersion(shared_ptr<Node> root, shared_ptr<Node> node);

	void coutTree(int deep, shared_ptr<Node> node);

public:
	Graph();

	void addVertex(shared_ptr<GeographicalObject> cost);

	shared_ptr<GeographicalObject> getVertex(long information);
	shared_ptr<GeographicalObject> getVertex(long information, int version);

	void coutTree();
	void coutTree(int version);
};