#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "Shapes/triangle.h"
#include "Shapes/plane.h"
#include "Shapes/sphere.h"
#include "func.h"

std::string printPoint(float* point){
	std::stringstream sstm;
	sstm << "(" << point[0] << ", " << point[1] << ", " << point[2] << ")" ;
	return sstm.str();
}

std::string printPoint(const float* point){
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

float dot(float* pt1, const float* pt2){
	float x = pt1[0] * pt2[0];
	float y = pt1[1] * pt2[1];
	float z = pt1[2] * pt2[2];
	return x + y + z;
}

float dot(const float* pt1, float* pt2){
	float x = pt1[0] * pt2[0];
	float y = pt1[1] * pt2[1];
	float z = pt1[2] * pt2[2];
	return x + y + z;
}

float dot(const float* pt1, const float* pt2){
	float x = pt1[0] * pt2[0];
	float y = pt1[1] * pt2[1];
	float z = pt1[2] * pt2[2];
	return x + y + z;
}

float* cross(float* v1, float* v2, float* ret){
	ret[0] = v1[1]*v2[2] - v1[2]*v2[1];
	ret[1] = v1[2]*v2[0] - v1[0]*v2[2];
	ret[2] = v1[0]*v2[1] - v1[1]*v2[0];

	return ret;
}

float* sub(float* pt1, float* pt2, float* ret){
	ret[0] = pt1[0] - pt2[0];
	ret[1] = pt1[1] - pt2[1];
	ret[2] = pt1[2] - pt2[2];
	return ret;
}

float* sub(float* pt1, const float* pt2, float* ret){
	ret[0] = pt1[0] - pt2[0];
	ret[1] = pt1[1] - pt2[1];
	ret[2] = pt1[2] - pt2[2];
	return ret;
}

float* sub(const float* pt1, float* pt2, float* ret){
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
int* add(int* pt1, int* pt2, int* ret){
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

int* copy(int* pt1, int* ret){
	ret[0] = pt1[0];
	ret[1] = pt1[1];
	ret[2] = pt1[2];
	return ret;
}

float* copy(float* pt1, float* ret){
	ret[0] = pt1[0];
	ret[1] = pt1[1];
	ret[2] = pt1[2];
	return ret;
}

float norm(float* pt){
	return sqrt(pt[0] * pt[0] + pt[1] * pt[1] + pt[2] * pt[2]);
}

int closest(float* t, int n){
	int maxi = 0;
	float maxval = t[0];
	for(int i = 1; i < n; i++){
		if(t[i] > 0 && (t[i] < maxval || maxval < 0)){
			maxval = t[i];
			maxi = i;
		}
	}
	if(maxval < 0)
		return -1;
	else
		return maxi;
}