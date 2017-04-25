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
// Method:    AStarSearch  A*�㷨���ģ�����closed�������һ���ڵ㼴�յ�
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
					if (it != Open.end())//��open������ֻ��������
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
// Method:    PathCost  h(n)�����ۺ����������ȡ��򵥵Ĺ���ԭ��--���ֱ�߾���
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
// Method:    GetCostAround ����λ����Ϣ����ȡ��ͬ�Ļ���
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
// Method:    find  ��д��find������ֻ��������ȷ���Ƿ��ظ�
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
