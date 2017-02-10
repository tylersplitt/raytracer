#ifndef FUNC_H
#define FUNC_H

#include "triangle.h"
#include "plane.h"
#include "sphere.h"

#include <string>

std::string printPoint(float* point);
std::string printPoint(int* point);

float dot(float* pt1, float* pt2);
float* cross(float* v1, float* v2, float* ret);
float* sub(float* pt1, float* pt2, float* ret);
float* add(float* pt1, float* pt2, float* ret);
int* add(int* pt1, int* pt2, int* ret);
float* mult(float* pt, float x, float* ret);
int* mult(int* pt, float x, int* ret);
float* div(float* pt, float x, float* ret);
float norm(float* pt);
int* copy(int* pt1, int* ret);

int closest(float* t,int n);

#endif