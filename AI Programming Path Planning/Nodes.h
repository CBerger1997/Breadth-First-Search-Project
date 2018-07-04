#ifndef _Nodes_
#define _Nodes_

#include <list>

class Nodes
{
public:
	Nodes(int);
	~Nodes() {};

	void SetNodeValues(int, int );
	int GetNodeValues(int);

	void SetNode_x(int, int);
	int GetNode_x(int);

	void SetNode_y(int,int);
	int GetNode_y(int);

	void SetStartNode(int);
	int GetStartNode();

	void SetEndNode(int);
	int GetEndNode();

	void SetClosedNodes(bool, int);
	bool GetClosedNodes(int);

	int GetTotalNodes();
	int GetGrid_x();
	int GetGrid_y();


private:
	
	int TotalNodes;
	int Grid_x;
	int Grid_y;
	int *NodeValues;
	int *Node_x;
	int *Node_y;
	int StartNode;
	int EndNode;
	bool *ClosedNodes ;

}Node(150);

Nodes::Nodes(int TN)
{
	TotalNodes = TN;
	Grid_x = 15;
	Grid_y = 10;
	ClosedNodes = new bool[TN];
	NodeValues = new int[TN];
	Node_x = new int[TN];
	Node_y = new int[TN];
	StartNode = TotalNodes + 1;
	EndNode = TotalNodes + 1;
};

void Nodes::SetNodeValues(int n, int arrayn)
{
	NodeValues[arrayn] = n;
};
int Nodes::GetNodeValues(int arrayn)
{

	return NodeValues[arrayn];
};

void Nodes::SetNode_x(int x, int arrayn)
{
	Node_x[arrayn] = x;
};
int Nodes::GetNode_x(int arrayn)
{
	return Node_x[arrayn];
};

void Nodes::SetNode_y(int y, int arrayn)
{
	Node_y[arrayn] = y;
};
int Nodes::GetNode_y(int arrayn)
{
	return Node_y[arrayn];
};

void Nodes::SetStartNode(int s)
{
	StartNode = s;
}
int Nodes::GetStartNode()
{
	return StartNode;
}

void Nodes::SetEndNode(int e)
{
	EndNode = e;
}
int Nodes::GetEndNode()
{
	return EndNode;
}

void Nodes::SetClosedNodes(bool c, int arrayn)
{
	ClosedNodes[arrayn] = c;
};
bool Nodes::GetClosedNodes(int arrayn)
{
	return ClosedNodes[arrayn];
};

int Nodes::GetTotalNodes()
{
	return TotalNodes;
}
int Nodes::GetGrid_x()
{
	return Grid_x;
}
int Nodes::GetGrid_y()
{
	return Grid_y;
}


#endif //Defines _Nodes_