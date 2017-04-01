#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Util/ray.h"
#include "Util/point3D.h"
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
		Point3D<float>* getMin();
		float getMinX();
		float getMinY();
		float getMinZ();
		Point3D<float>* getMax();
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

		int getInd(Point3D<float> pt);
		float intersectRay(Ray *&ray);
		int getFirstCell(Ray *&ray);
		int getNextCell(Ray *&ray, int curInd);


};
#endif