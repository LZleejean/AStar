#pragma once
#include "Location.h"
#include "AdjoinRelation.h"
#include "Resource.h"
#include <vector>

using namespace std;

class Node
{
public:
	Node(Location l) :loc(l){}
	Node(Location l, Node* p, int m, int n) :loc(l), parent(p), CostFromStart(m), CostToGoal(n){};
	~Node();

	void AroundNode(vector<Node> &nodes);
	bool operator>(const Node &n)const;
	bool operator<(const Node &n)const;
	bool operator==(const Node &n)const;
	
	Location GetLoc() const { return loc; }
	void SetLoc(Location val) { loc = val; }
	int GetCostFromStart() const { return CostFromStart; }
	void SetCostFromStart(int val) { CostFromStart = val; }
	int GetCostToGoal() const { return CostToGoal; }
	void SetCostToGoal(int val) { CostToGoal = val; }
	Node* GetParent() const { return parent; }
	void SetParent(Node* val) { parent = val; }
	int GetRe() const { return re; }
	void SetRe(int val) { re = val; }
private:
	Location loc;
	Node* parent;
	int CostFromStart;
	int CostToGoal;
	int re;
};

bool Node::operator>(const Node &n) const
{
	return CostFromStart + CostToGoal > n.CostFromStart + n.CostToGoal;
}
bool Node::operator<(const Node &n) const
{
	return CostFromStart + CostToGoal < n.CostFromStart + n.CostToGoal;
}
bool Node::operator==(const Node &n) const
{
	return CostFromStart + CostToGoal == n.CostFromStart + n.CostToGoal;
}


Node::~Node()
{

}

//************************************
// Method:    AroundNodes		用以获得某个节点周围的8个节点
// FullName:  AroundNodes
// Access:    public 
// Returns:   std::vector<Node>
// Qualifier:
//************************************
void Node::AroundNode(vector<Node> &nodes)
{

	if (loc.GetXPosition() - 1 >= 0)
	{
		Node newNode(Location(loc.GetXPosition() - 1, loc.GetYPosition()));
		newNode.SetRe(STRIGHT);
		nodes.push_back(newNode);
		if (loc.GetYPosition() - 1 >= 0)
		{
			Node newNode(Location(loc.GetXPosition() - 1, loc.GetYPosition() - 1));
			newNode.SetRe(DIAGONAL);
			nodes.push_back(newNode);
			Node newNode1(Location(loc.GetXPosition(), loc.GetYPosition() - 1));
			newNode.SetRe(DIAGONAL);
			nodes.push_back(newNode1);
		}
		if (loc.GetYPosition() + 1 <= YLENTH)
		{
			Node newNode(Location(loc.GetXPosition() - 1, loc.GetYPosition() + 1));
			newNode.SetRe(DIAGONAL);
			nodes.push_back(newNode);
			Node newNode1(Location(loc.GetXPosition(), loc.GetYPosition() + 1));
			newNode.SetRe(DIAGONAL);
			nodes.push_back(newNode1);
		}
	}
	if (loc.GetXPosition() + 1 <= XLENTH)
	{
		Node newNode(Location(loc.GetXPosition() + 1, loc.GetYPosition()));
		newNode.SetRe(STRIGHT);
		nodes.push_back(newNode);
		if (loc.GetYPosition() - 1 >= 0)
		{
			Node newNode(Location(loc.GetXPosition() + 1, loc.GetYPosition() - 1));
			newNode.SetRe(DIAGONAL);
			nodes.push_back(newNode);
		}
		if (loc.GetYPosition() + 1 <= YLENTH)
		{
			Node newNode(Location(loc.GetXPosition() + 1, loc.GetYPosition() + 1));
			newNode.SetRe(DIAGONAL);
			nodes.push_back(newNode);
		}
	}
}


