#pragma once


//#include "GeographicalObject.h"
#include <string>
#include <vector>
#include <iostream>


using namespace std;


class GeographicalObject;


class Graph
{
	//Fibonacci Heap
	class FibonacciHeap
	{
		struct Node
		{
			pair<int, int> cost;

			shared_ptr<Node> child,
				left,
				right,
				parent;

			int degree;

			bool mark;

			Node();
			Node(pair<int, int> cost);
		};

		int size;
		shared_ptr<Node> root;

	public:
		FibonacciHeap();
		FibonacciHeap(pair<int, int> cost);
		
		bool empty();

		void unionLists(shared_ptr<Node> first, shared_ptr<Node> second);

		void insert(pair<int, int> cost);

		void consolidate();

		pair<int, int> getMinimum();

		pair<int, int> extractMinimum();

		void coutTree(int deep, shared_ptr<Node> node, shared_ptr<Node> begin);

		void coutTree();
	};
	
	//Graph
	vector<shared_ptr<GeographicalObject> > costs;

	vector<vector<pair<int, int> > > graph;
	int number;

	void getLinks();

	vector<vector<int> > johnson(vector<vector<pair<int, int> > > &graph);

	bool bellmanFord(vector<vector<pair<int, int> > > &graph, int vertex, vector<vector<int> > &weights, vector<int> &distance);

	void dijkstra(vector<vector<pair<int, int> > > &graph, int vertex, vector<vector<int> > &weights, vector<int> &distance);

	void coutMatrix(vector<vector<int> > &weights);

public:
	Graph();

	void addVertexes(vector<shared_ptr<GeographicalObject> > costs);

	void coutGraph();
};