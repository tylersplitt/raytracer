#include "ray.h"
#include "func.h"

Ray :: Ray(float* ori, float* dir){
	origin = ori;
	direction= dir;
}

void Ray :: setOrigin(float* newOr){
	origin = newOr;
}

float* Ray :: getOrigin(){
	return origin;
}

void Ray :: setDirection(float* newDir){
	direction = newDir;
}

float* Ray :: getDirection(){
	return direction;
}

float* Ray :: getPoint(float t, float* ret){
	float temp[3] = {0,0,0};
	mult(direction,t,temp);
	add(origin,temp,ret);
	return ret;
}