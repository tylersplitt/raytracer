#include <iostream>
#include "ray.h"
#include "func.h"

Ray :: Ray(Point3D<float> ori, Point3D<float> dir){
	origin = ori;
	direction = dir;
}

Ray :: ~Ray(){
	// delete origin;
	// delete direction;
}

void Ray :: setOrigin(Point3D<float> newOr){
	origin = newOr;
}

Point3D<float> Ray :: getOrigin(){
	return origin;
}

void Ray :: setDirection(Point3D<float> newDir){
	direction = newDir;
}

Point3D<float> Ray :: getDirection(){
	return direction;
}

Point3D<float> Ray :: getPoint(float t){
	Point3D<float> ret;
	ret.setX(direction.getX() * t + origin.getX());
	ret.setY(direction.getY() * t + origin.getY());
	ret.setZ(direction.getZ() * t + origin.getZ());
	return ret;
}

float Ray :: timeToPoint(Point3D<float> pt){
	// std::cout << pt << std::endl;
	// std::cout << "o" << origin << std::endl;
	// std::cout << "d" << direction << std::endl;
	float xt = (pt.getX() - origin.getX())/direction.getX(); 
	float yt = (pt.getY() - origin.getY())/direction.getY(); 
	float zt = (pt.getZ() - origin.getZ())/direction.getZ();
	// std::cout << "xt = " << xt << " yt = " << yt << " zt = " << zt << std::endl;
	if(xt == yt && yt == zt)
		return xt;
	return -1; 
}

void Ray :: printRay() const{
	std::cout << "Ray Object {" << std::endl 
		<< "\tOrigin: " << origin << std::endl 
		<< "\tDirection: " << direction << std::endl 
		<< "}" << std::endl;
}