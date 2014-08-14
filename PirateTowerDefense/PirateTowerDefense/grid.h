#ifndef __GRID_H_
#define __GRID_H_

#include "glut.h"        // OpenGL utilties 

class Grid
{
public:
	int rowAm;
	int colAm;
	int boxSize;
	int startX;
	int startY;
	float r,g,b;
	Grid(int row, int col, int box, int sX, int sY, float r, float g, float b): rowAm(row), colAm(col), boxSize(box), startX(sX), startY(sY), r(r), g(g), b(b) {}
	
	void DrawGrid();
};

#endif