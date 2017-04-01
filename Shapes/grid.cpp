#include <iostream>
#include <string>
#include <math.h>
#include "grid.h"
#include "Util/func.h"
#include "Util/ray.h"

Grid :: Grid(float minx, float miny, float minz, int boxWidth_, int cellWidth_){
	boxWidth = boxWidth_;
	cellWidth = cellWidth_;
	Point3D<float>* min = new Point3D<float>(minx, miny, minz);
	Point3D<float>* max = new Point3D<float>(minx+boxWidth, miny+boxWidth, minz+boxWidth);
	box = new BB(min, max);
	eps = .0000001;

	rowCells = boxWidth/cellWidth;
    totCells = rowCells*rowCells*rowCells;
	gridCells = new std::vector<int>[totCells];
    counts = new int[totCells];
	for(int x = 0; x < totCells; x++)
		counts[x] = 0;
}
Grid :: Grid(){

}
Grid :: ~Grid(){
	delete box;
	delete [] gridCells;
	delete [] counts;
}
void Grid :: setGrid(float minx, float miny, float minz, int boxWidth_, int cellWidth_){
	boxWidth = boxWidth_;
	cellWidth = cellWidth_;
	Point3D<float>* min = new Point3D<float>(minx, miny, minz);
	Point3D<float>* max = new Point3D<float>(minx+boxWidth, miny+boxWidth, minz+boxWidth);
	box = new BB(min, max);
	eps = .0000001;

	rowCells = boxWidth/cellWidth;
    totCells = rowCells*rowCells*rowCells;
	gridCells = new std::vector<int>[totCells];
    counts = new int[totCells];
	for(int x = 0; x < totCells; x++)
		counts[x] = 0;
}
BB * Grid :: getBox(){
	return box;
}
Point3D<float>* Grid :: getMin(){
	return box->getMin();
}
float Grid :: getMinX(){
	return box->getMinX();
}
float Grid :: getMinY(){
	return box->getMinY();
}
float Grid :: getMinZ(){
	return box->getMinZ();
}
Point3D<float>* Grid :: getMax(){
	return box->getMax();
}
float Grid :: getMaxX(){
	return box->getMaxX();
}
float Grid :: getMaxY(){
	return box->getMaxY();
}
float Grid :: getMaxZ(){
	return box->getMaxZ();
}
int Grid :: getBoxWidth(){
	return boxWidth;
}
int Grid :: getCellWidth(){
	return cellWidth;
}
int Grid :: getTotCells(){
	return totCells;
}
int Grid :: getRowCells(){
	return rowCells;
}
std::vector<int>* Grid :: getGridCells(){
	return gridCells;
}
int* Grid :: getCounts(){
	return counts;
}
float Grid :: intersectRay(Ray *&ray){
	return box->intersectRay(ray);
}
//gets first cell the ray hits
int Grid :: getFirstCell(Ray *&ray){
	Point3D<float> ori = ray->getOrigin();
	if(box->inBox(ori)){
		return getInd(ori);
	}
	float t = box->intersectRay(ray);
	if(t < eps)
		return -1;
	Point3D<float> pt = ray->getPoint(t);
	// int i = getInd(pt);
	// std::cout << i << " " << ori << " " << pt << std::endl;
	return getInd(pt);
}
//Uses code similar to the bounding box intersection but uses 
//the tmax instead of tmin to get the second plane hit
int Grid :: getNextCell(Ray *&ray, int curInd){
	Point3D<float> dir = ray->getDirection();
	Point3D<float> ori = ray->getOrigin();

	int xind = curInd/(rowCells*rowCells);
	int yind = (curInd - (xind*rowCells*rowCells))/rowCells;
	int zind = curInd - yind*rowCells - xind*rowCells*rowCells;

	float minCellX = xind*cellWidth + box->getMinX(); 
	float maxCellX = minCellX + cellWidth;
	float minCellY = yind*cellWidth + box->getMinY(); 
	float maxCellY = minCellY + cellWidth;
	float minCellZ = zind*cellWidth + box->getMinZ(); 
	float maxCellZ = minCellZ + cellWidth;

	Point3D<float> min(minCellX,minCellY,minCellZ);
	Point3D<float> max(maxCellX,maxCellY,maxCellZ);

	float tx0,tx1,ty0,ty1,tz0,tz1,tmin,tmax;
	float invdir[3] = {1/dir[0],1/dir[1],1/dir[2]};
	if(invdir[0] >= 0){
		tx0 = (min[0] - ori[0])*invdir[0];
		tx1 = (max[0] - ori[0])*invdir[0];
	}
	else{
		tx0 = (max[0] - ori[0])*invdir[0];
		tx1 = (min[0] - ori[0])*invdir[0];
	}
	tmin = tx0;
	tmax = tx1;
	if(invdir[1] >= 0){
		ty0 = (min[1] - ori[1])*invdir[1];
		ty1 = (max[1] - ori[1])*invdir[1];
	}
	else{
		ty0 = (max[1] - ori[1])*invdir[1];
		ty1 = (min[1] - ori[1])*invdir[1];
	}
	if(ty0 > tmin)
		tmin = ty0;
	if(ty1 < tmax)
		tmax = ty1;
	if(invdir[2] >= 0){
		tz0 = (min[2] - ori[2])*invdir[2];
		tz1 = (max[2] - ori[2])*invdir[2];
	}
	else{
		tz0 = (max[2] - ori[2])*invdir[2];
		tz1 = (min[2] - ori[2])*invdir[2];
	}
	if(tz0 > tmin)
		tmin = tz0;
	if(tz1 < tmax)
		tmax = tz1;
	
	if(tmax == tx1){
		if(invdir[0] >= 0)
			xind++;
		else
			xind--;
	}
	if(tmax == ty1){
		if(invdir[1] >= 0)
			yind++;
		else
			yind--;
	}
	if(tmax == tz1){
		if(invdir[2] >= 0)
			zind++;
		else
			zind--;
	}
	if(xind < 0 || yind < 0 || zind < 0)
		return -1;
	if(xind >= rowCells || yind >= rowCells || zind >= rowCells)
		return -1;
	
	return xind*rowCells*rowCells+yind*rowCells+zind;
}
//Gets grid index from x,y,z values
int Grid :: getInd(Point3D<float> pt){
	if(!box->inBox(pt))
		return -1;
	int xind = (pt[0] - box->getMinX())/cellWidth;
	if(xind == rowCells)
		xind = rowCells - 1;
	int yind = (pt[1] - box->getMinY())/cellWidth;
	if(yind == rowCells)
		yind = rowCells - 1;
	int zind = (pt[2] - box->getMinZ())/cellWidth;
	if(zind == rowCells)
		zind = rowCells - 1;
	// std::cout << Point3D<int>(xind,yind,zind)  << std::endl;
	return xind*rowCells*rowCells + yind*rowCells + zind;
}