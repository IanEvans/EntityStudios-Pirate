#ifndef __DEF_H_
#define __DEF_H_

#include <fstream>
using namespace std;

class Defense
{
public:
	int health;
	int nodeOccupying;
	int defenseType;
	int xPos;
	int yPos;
	
	Defense(): health(0), xPos(0), yPos(0), nodeOccupying(-1), defenseType(0) {}
	Defense(int hp, int x, int y, int node, int type);

	void Update();
	friend ostream& operator<<(ostream&, const Defense&);
	~Defense(){}
};

#endif