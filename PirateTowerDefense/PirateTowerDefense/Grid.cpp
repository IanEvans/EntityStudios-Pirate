#include "grid.h"

void Grid::DrawGrid()  
{
	glPushMatrix();
		glColor3f(r,g,b);
		
		for(int i = 0; i < rowAm + 1; i++)
		{
			for(int j = 0; j < colAm + 1; j++)
			{
				//y axis lines
				glBegin(GL_LINES);
					glVertex2f(startX + (j * boxSize), startY);
					glVertex2f(startX + (j * boxSize), startY + (boxSize * i));
				glEnd();
				
				//x axis lines
				glBegin(GL_LINES);
					glVertex2f(startX, startY + (i * boxSize));
					glVertex2f(startX + (boxSize  * j), startY + (i * boxSize));
				glEnd();
			}
		}
	glPopMatrix();
}

