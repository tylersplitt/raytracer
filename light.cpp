#include <math.h>
#include <iostream>
#include "light.h"
#include "func.h"

Light :: Light(float* dir, float kd_, float illum_){
	direction= dir;
	kd = kd_;
	illum = illum_;
}

void Light :: setDirection(float* newDir){
	direction = newDir;
}

float* Light :: getDirection(){
	return direction;
}

void Light :: setKD(float newKD){
	kd = newKD;
}

float Light :: getKD(){
	return kd;
}

void Light :: setIllum(float newIllum){
	illum = newIllum;
}

float Light :: getIllum(){
	return illum;
}

int* Light :: phong(float* pt, float* norm, int* mat,int* ret){
	float factor = kd*illum*dot(norm,direction);
	if(factor < 0) 
		factor = 0;
	mult(mat, factor, ret);
	return ret;
}