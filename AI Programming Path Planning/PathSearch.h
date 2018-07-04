#ifndef _PathSearch_
#define _PathSearch_

#include <iostream>
#include <list>

class PathSearch
{
public:

	PathSearch(int);
	~PathSearch() {};
	void BreadthFirstSearch();
	void ShortestSearchPath();
	void NodeEdge(int, int);

	void SetPath(int, int);
	int GetPath(int);

private:
	std::list<int> *Adjacent;
	int path[150];
	int Distance[150];
}Grid(150);

PathSearch::PathSearch(int TN)
{
	Adjacent = new std::list<int>[TN];
	//path = new int[150];
};

void PathSearch::SetPath(int arrayn, int p)
{
	path[arrayn] = p;
}
int PathSearch::GetPath(int arrayn)
{
	return path[arrayn];
};

void PathSearch::NodeEdge(int a, int b)
{
	Adjacent[a].push_back(b);
};

void PathSearch::BreadthFirstSearch()
{
	//List variables, creates queue and iterator
	std::list<int> OpenQueue;
	std::list<int>::iterator i;

	//Bool variables, checks for closed nodes and whether the end node has been found
	bool Exit = false;

	//int variable, sets distance each node is from the start node
	int StartingNode = Node.GetStartNode();

	//for loop, sets all nodes to Open and all distance except start node to above the total node count
	for (int i = 0; i < Node.GetTotalNodes(); i++)
	{
		if (i == Node.GetStartNode())
		{
			Grid.Distance[i] = 0;
		}
		else
		{
			Grid.Distance[i] = Node.GetTotalNodes() + 1;
		};
	};

	//sets the start node to closed and adds the start node value to the end of BFSQueue
	Node.SetClosedNodes(true, Node.GetStartNode());
	OpenQueue.push_back(Node.GetStartNode());

	//While loop, loops while the OpenQueue is not empty
	while (OpenQueue.empty() == false)
	{
		int SearchNode = Node.GetStartNode();
		
		SearchNode = OpenQueue.front();
		OpenQueue.pop_front();

		//Gets all adjacent vertices to StartNode
		for (i = Adjacent[SearchNode].begin(); i != Adjacent[SearchNode].end(); ++i)
		{
			//marks adjacent node as closed if it is open, then adds node value to the back of queue
			if (Node.GetClosedNodes(*i) == false)
			{
				if (*i == Node.GetEndNode())
				{
					Node.SetClosedNodes(false, *i);
				}
				else
				{
					Node.SetClosedNodes(true, *i);
				}				
				OpenQueue.push_back(*i);
				Grid.Distance[*i] = Grid.Distance[SearchNode] + 1;
			};
			//Checks node to see if it is the end node or not, breaks loop if end node is found
			if (SearchNode == Node.GetEndNode())
			{
				Exit = true;
			};
		};
		if (Exit == true)
		{
			break;
		};
	};
	if (Exit != false)
	{
		ShortestSearchPath();
	}
	else
	{
		std::cout << "The End Node cannot be found/reached, Press 0 or 9 to restart" << std::endl;
	};
	//------------------SEPERATE THESE TWO PIECES OF CODE TO TWO DIFFERENT FUNCTIONS------------------
};

void PathSearch::ShortestSearchPath()
{
	//variables used to calculate the shortest path between the start and end node
	int SearchNode = Node.GetEndNode();
	int CloseDistance[4];
	int count = 0;
	bool StartNodeFound = false;
	int Tile[4];
	std::list<int>::iterator i;

	//prints out "shortest path" so it is clear in the console what the program is doing
	std::cout << " " << std::endl;
	std::cout << "SHORTEST PATH: " << SearchNode << " ";

	//while loop, finds the shortest path from the end node to the start node, breaking once the start node is found
	while (!StartNodeFound)
	{
		//resets count to 0
		count = 0;

		//resets the ClosedDistance array to 0 for all values
		for (int i = 0; i < 4; i++)
		{
			CloseDistance[i] = 0;
		};

		//for loop, checks adjacent nodes to current SearchNode, storing their distance and tile number in the CloseDistance and Tile arrays
		for (i = Adjacent[SearchNode].begin(); i != Adjacent[SearchNode].end(); ++i)
		{
			CloseDistance[count] = Grid.Distance[*i];
			Tile[count] = *i;
			count = count + 1;
			//checks to see whether the StartingNode has been found, breaking the for loop if it has
			if (*i == Node.GetStartNode())
			{
				StartNodeFound = true;
				break;
			};
		};

		//variable used to store the adjacent node with the shortest or joint shortest distance
		int shortestDist;

		//sets the shortestDist variable equal to the first adjacent nodes distance and sets the next SearchNode to the first adjacent node in case the first adjacent node has the shortest distance
		shortestDist = CloseDistance[0];
		SearchNode = Tile[0];

		//for loop, used to check which of the ClosedDistance values is the smallest or joint smallest and then sets the smallest distance node as the next SearchNode
		for (int i = 1; i < count; i++)
		{
			//if statement, checks to see if the next adjacent node has a shorter distance than the current shortest distance, replacing the current shortest distance and SearchNode if true
			if (CloseDistance[i] < shortestDist)
			{
				shortestDist = CloseDistance[i];
				SearchNode = Tile[i];
			}


		};
		//Stores the Node of each shortest distance in the Path variable in the PathSearch class, creating the shortest path and printing it
		if (SearchNode != Node.GetStartNode() && SearchNode != Node.GetEndNode())
		{
			Grid.SetPath(SearchNode, SearchNode);
		};
		std::cout << " " << SearchNode << " ";
	};
	//prints out "End of path" so that it is clear in the console what the program is doing
	std::cout << " END OF PATH " << std::endl;
	std::cout << "Press 4, 5, 6 or 7 to choose a new layout" << std::endl;
	std::cout << "Press 8 to restart with Start and End nodes" << std::endl;
	std::cout << "Press 9 to restart" << std::endl;
	std::cout << "Press 0 to wipe" << std::endl;
};

#endif //Defines _PathSearch_