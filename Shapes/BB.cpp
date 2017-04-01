#include <iostream>
#include <string>
#include <math.h>
#include "BB.h"
#include "Util/func.h"
#include "Util/ray.h"
#include "Util/point3D.h"

BB :: BB(Point3D<float>* min_, Point3D<float>* max_){
	min = min_;
	max = max_;
	eps = .0000001;
}
BB :: BB(){

}
BB :: ~BB(){
	delete min;
	delete max;
}	
void BB :: setBB(Point3D<float>* min_, Point3D<float>* max_){
	min = min_;
	max = max_;
	eps = .0000001;
}
void BB :: setMin(Point3D<float>* newMin){
	Point3D<float>* temp = min;
	min = newMin;
	delete temp;
}
Point3D<float>* BB :: getMin(){
	return min;
}
float BB :: getMinX(){
	return min->getX();
}
float BB :: getMinY(){
	return min->getY();
}
float BB :: getMinZ(){
	return min->getZ();
}
void BB :: setMax(Point3D<float>* newMax){
	Point3D<float>* temp = max;
	max = newMax;
	delete temp;
}
Point3D<float>* BB :: getMax(){
	return max;
}
float BB :: getMaxX(){
	return max->getX();
}
float BB :: getMaxY(){
	return max->getY();
}
float BB :: getMaxZ(){
	return max->getZ();
}
void BB :: printBox() const{
	std::cout << "BB Object {" << std::endl 
		<< "\tMin: " << *min << std::endl 
		<< "\tMax: " << *max << std::endl 
		<< "}" << std::endl;
}

//http://gamedev.stackexchange.com/questions/23748/testing-whether-two-cubes-are-touching-in-space
bool BB :: overlap(BB *box){
	return ((min->getX() <= box->getMin()->getX() && box->getMin()->getX() <= max->getX()) || (box->getMin()->getX() <= min->getX() && min->getX() <= box->getMax()->getX())) &&
   ((min->getY() <= box->getMin()->getY() && box->getMin()->getY() <= max->getY()) || (box->getMin()->getY() <= min->getY() && min->getY() <= box->getMax()->getY())) &&
   ((min->getZ() <= box->getMin()->getZ() && box->getMin()->getZ() <= max->getZ()) || (box->getMin()->getZ() <= min->getZ() && min->getZ() <= box->getMax()->getZ())); 
}

bool BB :: inBox(Point3D<float> pt){
	return ((min->getX() <= pt[0] && pt[0] <= max->getX()) && (min->getY() <= pt[1] && pt[1] <= max->getY()) && (min->getZ() <= pt[2] && pt[2] <= max->getZ()));
}

//based off code from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
float BB :: intersectRay(Ray *&ray){
	Point3D<float> dir = ray->getDirection();
	Point3D<float> ori = ray->getOrigin();

	float tx0,tx1,ty0,ty1,tz0,tz1,tmin,tmax;
	Point3D<float> invdir(1/dir.getX(),1/dir.getY(),1/dir.getZ());
	if(invdir[0] >= 0){
		tx0 = (min->getX() - ori.getX())*invdir[0];
		tx1 = (max->getX() - ori.getX())*invdir[0];
	}
	else{
		tx0 = (max->getX() - ori.getX())*invdir[0];
		tx1 = (min->getX() - ori.getX())*invdir[0];
	}
	tmin = tx0;
	tmax = tx1;
	if(invdir[1] >= 0){
		ty0 = (min->getY() - ori.getY())*invdir[1];
		ty1 = (max->getY() - ori.getY())*invdir[1];
	}
	else{
		ty0 = (max->getY() - ori.getY())*invdir[1];
		ty1 = (min->getY() - ori.getY())*invdir[1];
	}
	if((tmin > ty1) || (ty0 > tmax))
		return -1;
	if(ty0 > tmin)
		tmin = ty0;
	if(ty1 < tmax)
		tmax = ty1;
	if(invdir[2] >= 0){
		tz0 = (min->getZ() - ori.getZ())*invdir[2];
		tz1 = (max->getZ() - ori.getZ())*invdir[2];
	}
	else{
		tz0 = (max->getZ() - ori.getZ())*invdir[2];
		tz1 = (min->getZ() - ori.getZ())*invdir[2];
	}
	if((tmin > tz1) || (tz0 > tmax))
		return -1;
	if(tz0 > tmin)
		tmin = tz0;
	if(tz1 < tmax)
		tmax = tz1;
	return tmin;
}
