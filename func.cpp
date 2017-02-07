#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "func.h"

std::string printPoint(float* point){
	std::stringstream sstm;
	sstm << "(" << point[0] << ", " << point[1] << ", " << point[2] << ")" ;
	return sstm.str();
}

std::string printPoint(int* point){
	std::stringstream sstm;
	sstm << "(" << point[0] << ", " << point[1] << ", " << point[2] << ")" ;
	return sstm.str();
}

float dot(float* pt1, float* pt2){
	float x = pt1[0] * pt2[0];
	float y = pt1[1] * pt2[1];
	float z = pt1[2] * pt2[2];
	return x + y + z;
}

float* sub(float* pt1, float* pt2, float* ret){
	ret[0] = pt1[0] - pt2[0];
	ret[1] = pt1[1] - pt2[1];
	ret[2] = pt1[2] - pt2[2];
	return ret;
}

float* add(float* pt1, float* pt2, float* ret){
	ret[0] = pt1[0] + pt2[0];
	ret[1] = pt1[1] + pt2[1];
	ret[2] = pt1[2] + pt2[2];
	return ret;
}

float* mult(float* pt, float x, float* ret){
	ret[0] = pt[0] * x;
	ret[1] = pt[1] * x;
	ret[2] = pt[2] * x;
	return ret;
}

int* mult(int* pt, float x, int* ret){
	ret[0] = pt[0] * x;
	ret[1] = pt[1] * x;
	ret[2] = pt[2] * x;
	return ret;
}

float* div(float* pt, float x, float* ret){
	ret[0] = pt[0] / x;
	ret[1] = pt[1] / x;
	ret[2] = pt[2] / x;
	return ret;
}

float norm(float* pt){
	return sqrt(pt[0] * pt[0] + pt[1] * pt[1] + pt[2] * pt[2]);
}