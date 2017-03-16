#include <iostream>
#include <string>
#include <math.h>
#include "BB.h"
#include "Main/func.h"
#include "Main/ray.h"

BB :: BB(float* min_, float* max_){
	min = min_;
	max = max_;
	eps = .0000001;
}
BB :: BB(){

}
BB :: ~BB(){
	delete [] min;
	delete [] max;
}
void BB :: setBB(float* min_, float* max_){
	min = min_;
	max = max_;
	eps = .0000001;
}
void BB :: setMin(float* newMin){
	min = newMin;
}
float* BB :: getMin(){
	return min;
}
float BB :: getMinX(){
	return min[0];
}
float BB :: getMinY(){
	return min[1];
}
float BB :: getMinZ(){
	return min[2];
}
void BB :: setMax(float* newMax){
	max = newMax;
}
float* BB :: getMax(){
	return max;
}
float BB :: getMaxX(){
	return max[0];
}
float BB :: getMaxY(){
	return max[1];
}
float BB :: getMaxZ(){
	return max[2];
}
void BB :: printBox() const{
	std::cout << "BB Object {" << std::endl 
		<< "\tMin: " << printPoint(min) << std::endl 
		<< "\tMax: " << printPoint(max) << std::endl 
		<< "}" << std::endl;
}

//http://gamedev.stackexchange.com/questions/23748/testing-whether-two-cubes-are-touching-in-space
bool BB :: overlap(BB *box){
	return ((min[0] <= box->getMin()[0] && box->getMin()[0] <= max[0]) || (box->getMin()[0] <= min[0] && min[0] <= box->getMax()[0])) &&
   ((min[1] <= box->getMin()[1] && box->getMin()[1] <= max[1]) || (box->getMin()[1] <= min[1] && min[1] <= box->getMax()[1])) &&
   ((min[2] <= box->getMin()[2] && box->getMin()[2] <= max[2]) || (box->getMin()[2] <= min[2] && min[2] <= box->getMax()[2])); 
}

bool BB :: inBox(float* pt){
	return ((min[0] <= pt[0] && pt[0] <= max[0]) && (min[1] <= pt[1] && pt[1] <= max[1]) && (min[2] <= pt[2] && pt[2] <= max[2]));
}

//based off code from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
float BB :: intersectRay(Ray *&ray){
	const float * dir = ray->getDirection();

	const float * ori = ray->getOrigin();

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
	if((tmin > ty1) || (ty0 > tmax))
		return -1;
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
	if((tmin > tz1) || (tz0 > tmax))
		return -1;
	if(tz0 > tmin)
		tmin = tz0;
	if(tz1 < tmax)
		tmax = tz1;
	return tmin;
}
