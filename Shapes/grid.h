#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Main/ray.h"
#include "Shapes/BB.h"

class Grid
{
	private :
		BB * box;
		int boxWidth;
		int cellWidth;
		int totCells;
		int rowCells;
		std::vector<int>* gridCells;
		int * counts;
		float eps;

	public : 
		Grid(float minx, float miny, float minz, int boxWidth_, int cellWidth_);
		Grid();
		~Grid();
		void setGrid(float minx, float miny, float minz, int boxWidth_, int cellWidth);
		BB * getBox();
		float* getMin();
		float getMinX();
		float getMinY();
		float getMinZ();
		float* getMax();
		float getMaxX();
		float getMaxY();
		float getMaxZ();
		void setBoxWidth(int newBW);
		int getBoxWidth();
		void setCellWidth(int newCW);
		int getCellWidth();
		int getTotCells();
		int getRowCells();
		std::vector<int>* getGridCells();
		int* getCounts();

		int getInd(float* pt);
		float intersectRay(Ray *&ray);
		int getFirstCell(Ray *&ray);
		int getNextCell(Ray *&ray, int curInd);


};
#endif