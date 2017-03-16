#include <iostream>
#include "ray.h"
#include "func.h"

Ray :: Ray(float* ori, float* dir){
	origin = ori;
	direction = dir;
}

Ray :: ~Ray(){
	delete [] origin;
	delete [] direction;
}

// void Ray :: setOrigin(float* newOr){
// 	origin[0] = newOr[0];
// 	origin[1] = newOr[1];
// 	origin[2] = newOr[2];
// }

const float* Ray :: getOrigin(){
	return origin;
}

// void Ray :: setDirection(float* newDir){
// 	direction[0] = newDir[0];
// 	direction[1] = newDir[1];
// 	direction[2] = newDir[2];
// }

const float* Ray :: getDirection(){
	return direction;
}

float* Ray :: getPoint(float t, float* ret){
	ret[0] = direction[0] * t + origin[0];
	ret[1] = direction[1] * t + origin[1];
	ret[2] = direction[2] * t + origin[2];
	return ret;
}

void Ray :: printRay() const{
	std::cout << "Ray Object {" << std::endl 
		<< "\tOrigin: " << printPoint(origin) << std::endl 
		<< "\tDirection: " << printPoint(direction) << std::endl 
		<< "}" << std::endl;
}