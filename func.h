#ifndef FUNC_H
#define FUNC_H

#include <string>

std::string printPoint(float* point);
std::string printPoint(int* point);

float dot(float* pt1, float* pt2);
float* sub(float* pt1, float* pt2, float* ret);
float* add(float* pt1, float* pt2, float* ret);
float* mult(float* pt, float x, float* ret);
int* mult(int* pt, float x, int* ret);
float* div(float* pt, float x, float* ret);
float norm(float* pt);

#endif