#include <iostream>
#include <string>
using namespace std;
#ifndef GRAPH_H
#define GRAPH_H

struct vertex {
	string name;
	int level = 0;
};

struct ns {
	vertex *v;
	ns *next;
};

struct list {
	string key;
	vertex *v;
	ns* nroot;
	list* next;
};

ns* addToRoot(vertex*, ns*);
void removeNeighbour(list*, vertex*, ns*);
void printNeighbours(ns*);

list* addNode(vertex*, list*);
list* findNode(list*, string);
void printList(list*);

class graph {

	int size;
	int maxsize;
	bool directed;

public:
	list ** vs;
	graph(bool, int);
	int hashF(string);
	void addvertex(vertex*);
	void addEdge(vertex*, vertex*);
	void removeEdge(vertex*, vertex*);
	bool isEdge(vertex*, vertex*);
	void removeVertex(vertex*);
	void printgraph();
	void aroundgraph();
	void resize();
	vertex* findVertex(string key);
	int shortestPath(vertex*, vertex*);
};

void removeNode(graph*, int, list*, string);

#endif GRAPH_H