#pragma once

#include "Node.h"
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

int GetCostAround(const Node &n);
int PathCost(Location start, Location end);
Node* AStarSearch(Location StartLoc, Location EndLoc, list<Node>&, list<Node>&);
list<Node>::iterator find(list<Node> &, Node);

void main()
{
	Location s(5, 5),e(15,10);
	list<Node> Open, Closed;
	Node* endNode = AStarSearch(s, e,Open,Closed);
	for (; endNode->GetParent() != NULL;endNode=endNode->GetParent())
	{
		cout << endNode->GetLoc().ToString() << endl;
	}
	system("PAUSE");
}

//************************************
// Method:    AStarSearch  A*算法核心，返回closed表中最后一个节点即终点
// FullName:  AStarSearch
// Access:    public 
// Returns:   Node*
// Qualifier:
// Parameter: Location StartLoc
// Parameter: Location EndLoc
// Parameter: list<Node> & Open
// Parameter: list<Node> & Closed
//************************************
Node* AStarSearch(Location StartLoc, Location EndLoc, list<Node> &Open, list<Node> &Closed)
{
	Node StartNode(StartLoc, NULL, 0, PathCost(StartLoc, EndLoc));
	Open.push_back(StartNode);
	while (!Open.empty())
	{
		//Node *node = NULL;
		Closed.push_back(Open.front());
		Open.pop_front();
		//list<Node>::iterator it = find(Closed.begin(),Closed.end(),node);
		if (Closed.back().GetLoc().GetXPosition() == EndLoc.GetXPosition() && Closed.back().GetLoc().GetYPosition() == EndLoc.GetYPosition())
		{
			cout << "success" << endl;
			return &Closed.back();
		}
		else
		{
			vector<Node> nodes;
			Closed.back().AroundNode(nodes);
			for each (Node n in nodes)
			{
				int NewCost = Closed.back().GetCostFromStart() + GetCostAround(n);
				list<Node>::iterator it;
				it = find(Open,n);
				if (find(Closed, n) != Closed.end() || (it != Open.end() && Closed.back().GetCostFromStart() <= NewCost))
				{
					continue;
				}
				else
				{
					if (it != Open.end())//在open表中则只更新数据
					{
						/*n.SetParent(node);
						n.SetCostFromStart(NewCost);
						n.SetCostToGoal(PathCost(n.GetLoc(), EndLoc));*/
						it->SetParent(&Closed.back());
						it->SetCostFromStart(NewCost);
						it->SetCostToGoal(PathCost(n.GetLoc(), EndLoc));
					}
					else
					{
						n.SetParent(&Closed.back());
						n.SetCostFromStart(NewCost);
						n.SetCostToGoal(PathCost(n.GetLoc(), EndLoc));
						Open.push_back(n);
					}				
				}
			}
				
		}
		Open.sort();
	}
	Node *NullNode = NULL;
	cout << "NULL" << endl;
	return NullNode;
}

//************************************
// Method:    PathCost  h(n)，估价函数。这里采取最简单的估价原则--最短直线距离
// FullName:  PathCost
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: Location start
// Parameter: Location end
//************************************
int PathCost(Location start, Location end)
{
	int cost, dX, dY;
	dX = abs(end.GetXPosition() - start.GetXPosition());
	dY = abs(end.GetYPosition() - start.GetYPosition());
	cost = abs(dX - dY)*STRIGHTCOST + (dX > dY ? dY : dX)*DIAGONALCOST;
	return cost;
}

//************************************
// Method:    GetCostAround 根据位置信息，获取不同的花费
// FullName:  GetCostAround
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: const Node & n
//************************************
int GetCostAround(const Node &n)
{
	if (n.GetRe() == STRIGHT)
	{
		return STRIGHTCOST;
	}
	else
	{
		return DIAGONALCOST;
	}
}

//************************************
// Method:    find  重写了find方法，只根据坐标确定是否重复
// FullName:  find
// Access:    public 
// Returns:   std::list<Node>::iterator
// Qualifier:
// Parameter: list<Node> & l
// Parameter: Node n
//************************************
list<Node>::iterator find(list<Node> &l, Node n)
{
	list<Node>::iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		if (it->GetLoc().GetXPosition() == n.GetLoc().GetXPosition() && it->GetLoc().GetYPosition() == n.GetLoc().GetYPosition())
		{
			return it;
		}
	}
	return it;
}
