
#include "Graph.h"
#include <list>
using namespace std;

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
	return arrayOfList[u];
}
void Graph::AddEdge(int u, int v)
{
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

Graph Graph::MakeGtrans() const
{

}
vector<int> Graph::DFS(vector<int> mainLoop) const
{

}

void Graph::MakeSuperGraph(int& verteices, int& edges) const
{

}
