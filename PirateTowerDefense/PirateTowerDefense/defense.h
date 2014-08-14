#ifndef __DEF_H_
#define __DEF_H_

#include "StateMachine.h"
#include "defenseStates.h"

class Defense
{
private:
	StateMachine<Defense>* vStateMachine;

public:
	int health;
	int nodeOccupying;
	int defenseType;
	int xPos;
	int yPos;
	
	Defense(int x, int y, int node, int type);

	void DrawDefense();
	void Update();
	~Defense(){delete vStateMachine;}
	StateMachine<Defense>* GetSM() const { return vStateMachine; }
};

#endif