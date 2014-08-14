#include "defense.h"
#include <iostream>
#include "glut.h"

Defense::Defense(int x, int y, int node, int type)
{
	health = 100;
	nodeOccupying = node;
	defenseType = type;
	xPos = x;
	yPos = y;	
	vStateMachine = new StateMachine<Defense>(this);
	vStateMachine->SetCurrentState(Idle::Instance());
}

void Defense::Update()
{
	std::cout << "Updating defense" << std::endl;
	vStateMachine->Update();
}

void Defense::DrawDefense()
{
	int size = 28;
	glPushMatrix();
	switch(defenseType){
	case 0:
		glColor3f(0.0, 0.0, 1.0);
		break;
	case 1:
		glColor3f(1.0, 1.0, 1.0);
		break;
	}
	glBegin(GL_QUADS);
		glVertex2f(float(xPos - size), float(yPos - size));
		glVertex2f(float(xPos + size), float(yPos - size));
		glVertex2f(float(xPos + size), float(yPos + size));
		glVertex2f(float(xPos - size), float(yPos + size));
	glEnd();

	glPopMatrix();
}