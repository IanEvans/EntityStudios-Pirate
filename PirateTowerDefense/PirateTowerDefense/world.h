#ifndef __WORLD_H_
#define __WORLD_H_

#include "grid.h"
#include "node.h"

class World
{
	public:

		World();

		~World()
		{
			for(int i = 0; i < oceanRow * oceanCol; i++){
				if(oceanNodeList[i].defense != NULL)
					oceanNodeList[i].defense = NULL; //need to delete defense as well - here or in node or in defense deconstructor?
			}

			for(int i = 0; i < baseRow * baseCol; i++){
				if(baseNodeList[i].defense != NULL)
					baseNodeList[i].defense = NULL; //need to delete defense as well - here or in node or in defense deconstructor?
			}

			delete [] oceanNodeList; 
			delete [] baseNodeList;
			delete oceanGrid;
			delete baseGrid;
		};  

		int boxSize;
		int oceanRow;
		int oceanCol;
		int baseRow;
		int baseCol;
		int oceanStartX;
		int oceanStartY;
		int baseStartX;
		int baseStartY;

		//size determined at compile time so work this out in constructor
		Node * oceanNodeList; 
		Node * baseNodeList;
		Grid * oceanGrid;
		Grid * baseGrid;

		void CreateNodes();
		void CheckNeighbors(void) const;
		void SetNext(void);
		void RandomizeNodes(void);
		void ClearWorld(void);
		void DrawNodes() const;
		void CreateDefense(Node node, int type);
		void DrawDefenses() const;
};
#endif