#ifndef __NODE_H_
#define __NODE_H_

#include "defense.h"
#include <iostream>
#include "glut.h"
#include "SOIL.h"


class Node
{
public:
	int x;
	int y;
	int nodeType; // could be enum
	int row;
	int column;
	float size;
	int nodeID;
	Defense * defense;
	GLuint texture[2];

	Node(): x(0), y(0), row(0), column(0){
		defense = 0;
	}

	~Node()
	{
		//delete defense pointer details the NULL?
		//defense = NULL;
	}


	void DrawNode();
	void LoadTexture(void);
	void DrawNodeTexture(void);
};

#endif