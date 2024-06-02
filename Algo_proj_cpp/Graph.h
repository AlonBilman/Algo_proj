#pragma once
#include <list>
#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:

	int verteices_number=0; 
	int edges_number=0;
	vector<list<int>> arrayOfList;
	vector<int> arrayOfRoots;


public:

	void setVerteicesNumber(const int number);
	void setEdgesNumber(const int number);

	void MakeEmptyGraph();
	bool IsAdjacent(int u, int v)  ;
	list<int> GetAdjList(int u) const;
	void AddEdge(int v, int u);
	void RemoveEdge(int u, int v);

	vector<int> DFS(vector<int> mainLoop) const;

	Graph MakeGtrans() const;

	void MakeSuperGraph(int& verteices, int& edges) const;





};

