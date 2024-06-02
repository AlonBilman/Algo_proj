
#include "Graph.h"
#include <list>
using namespace std;

#define GRAY 1
#define WHITE 0
#define BLACK 2

Graph::~Graph()
{
	if (TransposeGraph)
		delete TransposeGraph;
}
void Graph::setVerteicesNumber(const int number)
{
	verteices_number = number;
}
void Graph::setEdgesNumber(const int number)
{
	edges_number = number;
}
void Graph::MakeEmptyGraph()
{
	arrayOfList.resize(verteices_number); //resize the list of neighbors to contain |vertex| elements
	arrayOfRoots.reserve(verteices_number); //resize the root array to have |vertex| elements
}
bool Graph::IsAdjacent(int u, int v) 
{
	--u; 
	list<int>::iterator i = arrayOfList[u].begin();

	for (i; i != arrayOfList[u].end(); ++i)
	{
		if (*i == v)
			return true;
	}
	return false;
	
}
list<int> Graph::GetAdjList(int u) const
{
	--u;
	return arrayOfList[u];
}
void Graph::AddEdge(int u, int v)
{
	--u;
	list<int>::iterator i = arrayOfList[u].begin();
	for (i; i != arrayOfList[u].end(); ++i)
	{
		try 
		{
			if (*i == v)
				throw("There is already a edge like this");
		}
		catch (string error)
		{
			cout << error << endl;
			exit(1);
		}
	}
	arrayOfList[u].push_back(v); //added a u->v
}
void Graph::RemoveEdge(int u, int v)
{
	--u;
	list<int>::iterator i = arrayOfList[u].begin();
	try 
	{
		for (i; i != arrayOfList[u].end(); ++i)
		{
			if (*i == v)
			{
				arrayOfList[u].remove(v); //remove v from the list.
				return;
			}
		}
		throw("There is not such an edge..");
	}
	catch (string error)
	{
		cout << error << endl;
		exit(1);
	}
}
void Graph::MakeGtrans()
{
	TransposeGraph = new Graph;
	TransposeGraph->setEdgesNumber(edges_number);  
	TransposeGraph->setVerteicesNumber(verteices_number); 
	TransposeGraph->MakeEmptyGraph();
	for (int i = 1; i <= verteices_number; ++i)
	{
		list<int> adjlist = this->GetAdjList(i);
		for (list<int>::iterator itr = adjlist.begin(); itr != adjlist.end(); ++itr)
		{
			TransposeGraph->AddEdge(*itr, i);
		}
	}
}

vector<int> Graph::DFS(vector<int> mainLoop,int& verteices, int& edges) 
{
	
	vector<pair<int, int>> edgeCount;
	verteices = edges = 0;
	vector<int> start(verteices_number, 0);
	vector<int> end(verteices_number, 0);
	vector<int> color(verteices_number, WHITE);
	int counter = 0;
	
	//Main Loop 
	for (vector<int>::iterator itr = mainLoop.begin(); itr != mainLoop.end(); ++itr)
	{
		if (color[*itr] == WHITE)
		{
			++verteices;
			Visit(*itr, *itr, edges, start, end, color, counter);
		}
	}
	return end;
	//ver

	//visit = > edges
}

void Graph::MakeSuperGraph(int& verteices, int& edges)
{
	vector<int> mainLoop(verteices_number);
	iota(mainLoop.begin(), mainLoop.end(), 0); // fill the mainloop from 1 to |vertex|
	vector<int> endList = DFS(mainLoop,verteices, edges);
	this->MakeGtrans();
	reverse(endList.begin(), endList.end());
	TransposeGraph->DFS(endList, verteices, edges);
}

void Graph::Visit(int vertex, int currentRoot, int& edges,
	        vector<int>& start, vector<int>& end,vector<int>& color,int& counter,
			vector<pair<int, int>>& edgeCount)
{
	bool foundAnEdge = false;
	arrayOfRoots[vertex] = currentRoot;
	color[vertex] = GRAY;
	start[vertex] = counter++;
	list<int> adj = GetAdjList(vertex);
	for (list<int>::iterator itr = adj.begin(); itr != adj.end(); ++itr)
	{
		if (color[*itr] == WHITE)
		{
			Visit(*itr, currentRoot, edges, start, end, color, counter, edgeCount);
		}

		else if (color[*itr] == BLACK)
		{
			if (start[vertex] > start[*itr])  // if it a crossarc 
			{

				pair<int, int> temp = { arrayOfRoots[vertex],arrayOfRoots[*itr] };

				for (auto &pair : edgeCount)
				{
					if (pair == temp)
					{
						foundAnEdge = true;
					}
				}
				if (!foundAnEdge)
				{
					edgeCount.push_back(temp);
					++edges;
				}
					
						 //edges of the super graph 
						 //works only on dfs+Sharir algo
						 //when doing a regular dfs, these parametest wont be used.
						//this is not correct when using dfs with random mainloop.
			}
		}
	}
	color[vertex] = BLACK;
	end[vertex] = counter++;
}