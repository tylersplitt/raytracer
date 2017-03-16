#include <math.h>
#include <iostream>
#include "directional_l.h"
#include "Main/func.h"

DirectionalL :: DirectionalL(float* dir, float kd_, float illum_){
	direction= dir;
	kd = kd_;
	illum = illum_;
}

void DirectionalL :: setDirection(float* newDir){
	direction = newDir;
}

float* DirectionalL :: getDirection(){
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

int* DirectionalL :: phong(float* norm, int* mat,int* ret){
	float factor = kd*illum*dot(norm,direction);
	if(factor < 0) 
		factor = 0;
	mult(mat, factor, ret);
	return ret;
}