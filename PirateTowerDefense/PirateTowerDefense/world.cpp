#include <stdlib.h>

#include <iostream>
#include <sstream>

#include "world.h"

World::World()
{
	oceanStartX = 10;
	oceanStartY = 10;
	boxSize = 55;
	oceanRow = 5;
	oceanCol = 5;
	baseRow = 5;
	baseCol = 3;
	baseStartX = oceanStartX + (boxSize * oceanRow) + 5;
	baseStartY = oceanStartY;

	oceanNodeList = new Node[oceanRow * oceanCol]; 
	baseNodeList = new Node[baseRow * baseCol];
	oceanGrid = new Grid(oceanRow, oceanCol, boxSize, oceanStartX, oceanStartY, 1.0, 1.0, 1.0);
	baseGrid = new Grid(baseRow, baseCol, boxSize, baseStartX, baseStartY, 1.0, 1.0, 1.0);
}


void World::CreateNodes()
{
	int hs = oceanGrid->boxSize / 2;
	int hs2 = baseGrid->boxSize / 2;
	for(int j = 0; j < oceanGrid->rowAm; ++j)
	{
		for(int i = 0; i < oceanGrid->colAm; ++i)
		{
			int current = (j * oceanGrid->rowAm) + i;

			oceanNodeList[current].x = (oceanGrid->startX + hs) + (oceanGrid->boxSize * i);
			oceanNodeList[current].y = (oceanGrid->startY + hs) + (oceanGrid->boxSize * j);
			oceanNodeList[current].row = current % oceanGrid->colAm;
			oceanNodeList[current].column = current / oceanGrid->colAm; 
			oceanNodeList[current].nodeType = 0;
			oceanNodeList[current].size = 28;
			oceanNodeList[current].nodeID = current;
			std::cout << "Current ocean nodeID: " << current << " " << oceanNodeList[current].nodeID << std::endl;
		}
	}
	
	for(int i = 0; i < baseGrid->colAm; ++i)
	{
		for(int j = 0; j < baseGrid->rowAm; ++j)
		{
			int current = (j * baseGrid->rowAm) + i;
			baseNodeList[current].x = (baseGrid->startX + hs) + (baseGrid->boxSize * i);
			baseNodeList[current].y = (baseGrid->startY + hs) + (baseGrid->boxSize * j);
			baseNodeList[current].row = current % baseGrid->colAm;
			baseNodeList[current].column = current / baseGrid->colAm; 
			baseNodeList[current].nodeType = 1;
			baseNodeList[current].size = 28;
			baseNodeList[current].nodeID = current;
			std::cout << "Current nodeID: " << current << " " << baseNodeList[current].nodeID << std::endl;
		}
	}
}

void renderString(float x, float y, float z, void *font, char *string) 
{  
  char *c;
  glRasterPos2f(x,y);
  for (c=string; *c != '\0'; c++) 
  {
    glutBitmapCharacter(font, *c);
  }
}

void renderInt(int var, float x, float y, float z)
{
	glPushMatrix();
		//glColor3f(1,1,1);
		std::ostringstream stringB;
		stringB << var;
		std::string tmp = stringB.str();
		const char* cstr = tmp.c_str();
		renderString(x, y, z, GLUT_BITMAP_TIMES_ROMAN_10, (char*)cstr);
	glPopMatrix();
}

void World::DrawNodes() const
{
	for(int i = 0; i < oceanGrid->colAm * oceanGrid->rowAm; ++i){
			//oceanNodeList[i].DrawNode();
			//oceanNodeList[i].DrawNodeTexture();
			renderInt(oceanNodeList[i].nodeID, float(oceanNodeList[i].x), float(oceanNodeList[i].y), 0);
			//node ids are wrong direction I wanted them in - need look at : TO DO
	}

	for(int i = 0; i < baseGrid->colAm * baseGrid->rowAm; ++i){
			//baseNodeList[i].DrawNode();
			//baseNodeList[i].DrawNodeTexture();
		renderInt(baseNodeList[i].nodeID, float(baseNodeList[i].x), float(baseNodeList[i].y), 0);
	}

}

void World::DrawDefenses() const
{
	for(int i = 0; i < oceanGrid->colAm * oceanGrid->rowAm; ++i){
		if(oceanNodeList[i].defense != NULL)
			oceanNodeList[i].defense->DrawDefense();
	}

	for(int i = 0; i < baseGrid->colAm * baseGrid->rowAm; ++i){
		if(baseNodeList[i].defense != NULL)
			baseNodeList[i].defense->DrawDefense();
	}

}

void World::CreateDefense(Node node, int type)
{
	Defense * newDef = new Defense(node.x, node.y, node.nodeID, type);
	oceanNodeList[node.nodeID].defense = newDef;
}
/*
void World::RandomizeNodes(void)
{
	for(int i = 0; i < GRID_X * GRID_Y;++i)
	{
		nodes[i].isAlive = bool(rand() % 2);
	}
}

void World::CheckNeighbors(void) const 
{
	for(int i = 0; i < GRID_X * GRID_Y; ++i)
	{	
		next[i] = nodes[i].isAlive;

		int count = 0;

		//live neighbor check 
		//corner top left
		if(i == 0)
		{
			if(nodes[i + 1].isAlive)
				count++;
			if(nodes[i + GRID_Y].isAlive)
				count++;
			if(nodes[i + GRID_Y + 1].isAlive)
				count++;
			if(nodes[i + GRID_Y - 1].isAlive)
				count++;
			if(nodes[i + (GRID_Y * 2) - 1].isAlive)
				count++;
			if(nodes[i + (GRID_Y * (GRID_Y - 1))].isAlive)
				count++;
			if(nodes[i + (GRID_Y * GRID_Y) - 1].isAlive)
				count++;
			//std::cout << "Hitting i = 0. count: " << count << std::endl;
		}
		//corner top right
		else if(nodes[i].column == GRID_X - 1 && nodes[i].row == 0)
		{
			if(nodes[i + 1].isAlive)
				count++;
			if(nodes[i + GRID_Y - 1].isAlive)
				count++;
			if(nodes[0].isAlive)
				count++;
			if(nodes[1].isAlive)
				count++;
			if(nodes[GRID_Y - 1].isAlive)
				count++;
			if(nodes[i - 1].isAlive)
				count++;
			if(nodes[i - GRID_Y].isAlive)
				count++;
			if(nodes[i - (GRID_Y * 2)].isAlive)
				count++;
			//std::cout << "Hitting top right = 0. count: " << count << std::endl;
		}
		//corner bottom left
		else if(nodes[i].column == 0 && nodes[i].row == GRID_X - 1)
		{
			if(nodes[0].isAlive)
				count++;
			if(nodes[i - 1].isAlive)
				count++;
			if(nodes[i + 1].isAlive)
				count++;
			if(nodes[i + GRID_Y].isAlive)
				count++;
			if(nodes[i + GRID_Y - 1].isAlive)
				count++;
			if(nodes[i + (GRID_Y * (GRID_Y - 1))].isAlive)
				count++;
			if(nodes[i + (GRID_Y * (GRID_Y - 1) - 1)].isAlive)
				count++;
			if(nodes[i + (GRID_Y * (GRID_Y - 2) + 1)].isAlive)
				count++;
			//std::cout << "Hitting bot left. count: " << count << std::endl;
		}
		//corner bottom right
		else if(nodes[i].column == GRID_X - 1 && nodes[i].row == GRID_X - 1)
		{
			if(nodes[i - 1].isAlive)
				count++;
			if(nodes[i - GRID_Y + 1].isAlive)
				count++;
			if(nodes[i - GRID_Y].isAlive)
				count++;
			if(nodes[i - GRID_Y - 1].isAlive)
				count++;
			if(nodes[i - (GRID_Y * 2) + 1].isAlive)
				count++;
			if(nodes[0].isAlive)
				count++;
			if(nodes[GRID_Y - 1].isAlive)
				count++;
			if(nodes[GRID_Y - 2].isAlive)
				count++;
			//std::cout << "Hitting bot right. count: " << count << std::endl;
		}
		//check side - top
		else if(nodes[i].row == 0)
		{
			if(nodes[i - 1].isAlive)
				count++;
			if(nodes[i + 1].isAlive)
				count++;
			if(nodes[i - GRID_Y].isAlive)
				count++;
			if(nodes[i + GRID_Y].isAlive)
				count++;
			if(nodes[i + GRID_Y - 1].isAlive)
				count++;
			if(nodes[i + GRID_Y + 1].isAlive)
				count++;
			if(nodes[i - GRID_Y + 1].isAlive)
				count++;
			if(nodes[i + (GRID_Y * 2) - 1].isAlive)
				count++;
			//std::cout << "Hitting top. count: " << count << std::endl;
		}
		//check side - bottom
		else if(nodes[i].row == GRID_X - 1)
		{
			if(nodes[i - 1].isAlive)
				count++;
			if(nodes[i + 1].isAlive)
				count++;
			if(nodes[i - GRID_Y].isAlive)
				count++;
			if(nodes[i + GRID_Y].isAlive)
				count++;
			if(nodes[i - GRID_Y - 1].isAlive)
				count++;
			if(nodes[i - GRID_Y + 1].isAlive)
				count++;
			if(nodes[i + GRID_Y - 1].isAlive)
				count++;
			if(nodes[i - (GRID_Y * 2) + 1].isAlive)
				count++;
			//std::cout << "Hitting bot. count: " << count << std::endl;
		}
		//check side - left
		else if(nodes[i].column == 0)
		{
			if(nodes[i - 1].isAlive)
				count++;
			if(nodes[i + 1].isAlive)
				count++;
			if(nodes[i + GRID_Y].isAlive)
				count++;
			if(nodes[i + GRID_Y - 1].isAlive)
				count++;
			if(nodes[i + GRID_Y + 1].isAlive)
				count++;
			if(nodes[i + (GRID_Y * (GRID_Y - 1))].isAlive)
				count++;
			if(nodes[i + (GRID_Y * (GRID_Y - 1)) + 1].isAlive)
				count++;
			if(nodes[i + (GRID_Y * (GRID_Y - 1)) - 1].isAlive)
				count++;
			//std::cout << "Hitting left. count: " << count << std::endl;
		}
		//check side - right
		else if(nodes[i].column == GRID_X - 1)
		{
			if(nodes[i - 1].isAlive)
				count++;
			if(nodes[i + 1].isAlive)
				count++;
			if(nodes[i - GRID_Y].isAlive)
				count++;
			if(nodes[i - GRID_Y - 1].isAlive)
				count++;
			if(nodes[i - GRID_Y + 1].isAlive)
				count++;
			if(nodes[i - (GRID_Y * (GRID_Y - 1))].isAlive)
				count++;
			if(nodes[i - (GRID_Y * (GRID_Y - 1)) + 1].isAlive)
				count++;
			if(nodes[i - (GRID_Y * (GRID_Y - 1)) - 1].isAlive)
				count++;
			//std::cout << "Hitting right. count: " << count << std::endl;
		}
		//if not a side
		else
		{		
			if(nodes[i - 1].isAlive)
				count++;
			if(nodes[i + 1].isAlive)
				count++;
			if(nodes[i - GRID_Y].isAlive)
				count++;
			if(nodes[i + GRID_Y].isAlive)
				count++;
			if(nodes[i - GRID_Y - 1].isAlive)
				count++;
			if(nodes[i - GRID_Y + 1].isAlive)
				count++;
			if(nodes[i + GRID_Y - 1].isAlive)
				count++;
			if(nodes[i + GRID_Y + 1].isAlive)
				count++;
			//			std::cout << "Hitting any. count: " << count << std::endl;
		}


		//rule check
		if(nodes[i].isAlive && count < 2)
		{
			//nodes[i].isAlive = false;
			next[i] = false;
		}
		else if(nodes[i].isAlive && (count == 2 || count == 3))
		{
			//nodes[i].isAlive = true;
			next[i] = true;
		}
		else if(nodes[i].isAlive && count > 3)
		{
			//nodes[i].isAlive = false;
			next[i] = false;
		}
		else if(nodes[i].isAlive == false && count == 3)
		{
			//nodes[i].isAlive = true;
			next[i] = true;
		}
	}
	/*
	for(int i = 0; i < GRID_X * GRID_Y; ++i)
	{
		if(next[i] == true)
			std::cout << "Node to be live: " << i << std::endl;
	}
}

void World::SetNext(void)
{
	for(int i = 0; i < GRID_X * GRID_Y; ++i)
	{
		nodes[i].isAlive = next[i];
		next[i] = false;
	}
}

void World::ClearWorld(void)
{
	for(int i = 0; i < GRID_X * GRID_Y; ++i)
	{
		nodes[i].isAlive = false;
	}
}


*/
