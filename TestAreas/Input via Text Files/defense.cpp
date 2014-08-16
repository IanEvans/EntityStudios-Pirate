#include "defense.h"
#include <iostream>


Defense::Defense(int hp, int x, int y, int node, int type)
{
	health = hp;
	nodeOccupying = node;
	defenseType = type;
	xPos = x;
	yPos = y;	
	
}

void Defense::Update()
{
	std::cout << "Updating defense" << std::endl;
}

ostream& operator<<(ostream& os, const Defense& def)
{
	os << "--DEFENSE--"
	   << "\nHP: " << def.health
	   << "\nNODE: " << def.nodeOccupying
	   << "\nTYPE: " << def.defenseType
	   << "\nX: " << def.xPos
	   << "\nY: " << def.yPos << std::endl;
	return os;

}