#include <math.h>
#include <iostream>
#include "point_l.h"
#include "Main/func.h"

PointL :: PointL(float* pos, float kd_, float illum_){
	position = pos;
	kd = kd_;
	illum = illum_;
}

void PointL :: setPosition(float* newPos){
	position = newPos;
}

float* PointL :: getPosition(){
	return position;
}

float* PointL :: getDirectionTo(float* pt, float* ret){
	sub(position,pt,ret);
	return ret;
}

void PointL :: setKD(float newKD){
	kd = newKD;
}

float PointL :: getKD(){
	return kd;
}

void PointL :: setIllum(float newIllum){
	illum = newIllum;
}

float PointL :: getIllum(){
	return illum;
}

int* PointL :: phong(float* pt, float* norm_, int* mat, Ray *&ray, int* ret){
	float ldir[3] = {0,0,0};
	getDirectionTo(pt,ldir);
	div(ldir,norm(ldir),ldir);
	float raydirnorm[3] = {0,0,0};
	const float * dir = ray->getDirection();
	float rayDir[3] = {0,0,0};
	rayDir[0] = dir[0];
	rayDir[1] = dir[1];
	rayDir[2] = dir[2];
	div(rayDir,norm(rayDir),raydirnorm);
	//specular reflection calculation
	float sp = dot(norm_,ldir);
	float spec = pow(dot(raydirnorm,norm_)*sp,32);
	//diffuse and specular calculation
	float factor = kd*illum*dot(norm_,ldir) + spec;
	if(factor < 0) 
		factor = 0;
	if(factor > 1)
		factor = 1;
	mult(mat, factor, ret);
	return ret;
}