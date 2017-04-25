#pragma once
#include <string>
#include <sstream>
#include <iostream> 
class Location
{
public:
	Location(int x, int y) :xPosition(x),yPosition(y){}
	//bool operator==(Location &l)const;
	int GetXPosition() const { return xPosition; }
	void SetXPosition(int val) { xPosition = val; }
	int GetYPosition() const { return yPosition; }
	void SetYPosition(int val) { yPosition = val; }
	std::string ToString()const;
private:
	int xPosition;
	int yPosition;
};

std::string Location::ToString() const
{
	std::string s="";
	std::stringstream s1,s2;
	s1 << xPosition;
	s2 << yPosition;
	s = "(" + s1.str() + "," + s2.str() + ")";
	return s;
}

//bool Location::operator==(Location &l) const
//{
//	return (xPosition == l.GetXPosition() && yPosition == l.GetYPosition());
//}

