#include <math.h>
#include <iostream>
#include "directional_l.h"
#include "Util/func.h"

DirectionalL :: DirectionalL(Point3D<float> dir, float kd_, float illum_){
	direction = dir;
	kd = kd_;
	illum = illum_;
}

void DirectionalL :: setDirection(Point3D<float> newDir){
	direction = newDir;
}

Point3D<float> DirectionalL :: getDirection(){
	return direction;
}

void DirectionalL :: setKD(float newKD){
	kd = newKD;
}

float DirectionalL :: getKD(){
	return kd;
}

void DirectionalL :: setIllum(float newIllum){
	illum = newIllum;
}

float DirectionalL :: getIllum(){
	return illum;
}

Point3D<int> DirectionalL :: phong(Point3D<float> norm, Point3D<int> mat){
	float factor = kd*illum*direction.dot(norm);
	if(factor < 0) 
		factor = 0;
	return mat*factor;
}