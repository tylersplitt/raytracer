#include <iostream>
#include <string>
#include <math.h>
#include "Main/ray.h"
#include "triangle.h"
#include "Main/func.h"

Triangle :: Triangle(){

}

Triangle :: Triangle(float* pt1_, float* pt2_, float* pt3_, int* mat){
	pt1 = pt1_;
	pt2 = pt2_;
	pt3 = pt3_;
	setNormal(normal);
	D = dot(normal,pt1);
	area = getArea(pt1,pt2,pt3);
	material = mat;
	eps = .000001;
	float * min = new float[3];
	float * max = new float[3];
	for(int i = 0; i < 3; i++){
		if(pt1[i] > pt2[i] && pt1[i] > pt3[i])
			max[i] = pt1[i];
		if(pt2[i] > pt1[i] && pt2[i] > pt3[i])
			max[i] = pt2[i];
		if(pt3[i] > pt2[i] && pt3[i] > pt1[i])
			max[i] = pt3[i];
		if(pt1[i] < pt2[i] && pt1[i] < pt3[i])
			min[i] = pt1[i];
		if(pt2[i] < pt1[i] && pt2[i] < pt3[i])
			min[i] = pt2[i];
		if(pt3[i] < pt2[i] && pt3[i] < pt1[i])
			min[i] = pt3[i];
	}
	box = new BB(min,max);
}
Triangle :: ~Triangle(){
	delete [] pt1;
	delete [] pt2;
	delete [] pt3;
	delete [] material;
}
void Triangle :: setTri(float* pt1_, float* pt2_, float* pt3_, int* mat){
	pt1 = pt1_;
	pt2 = pt2_;
	pt3 = pt3_;
	setNormal(normal);
	D = dot(normal,pt1);
	area = getArea(pt1,pt2,pt3);
	material = mat;
	eps = .000001;
	float * min = new float[3];
	float * max = new float[3];
	for(int i = 0; i < 3; i++){
		if(pt1[i] > pt2[i] && pt1[i] > pt3[i])
			max[i] = pt1[i];
		if(pt2[i] > pt1[i] && pt2[i] > pt3[i])
			max[i] = pt2[i];
		if(pt3[i] > pt2[i] && pt3[i] > pt1[i])
			max[i] = pt3[i];
		if(pt1[i] < pt2[i] && pt1[i] < pt3[i])
			min[i] = pt1[i];
		if(pt2[i] < pt1[i] && pt2[i] < pt3[i])
			min[i] = pt2[i];
		if(pt3[i] < pt2[i] && pt3[i] < pt1[i])
			min[i] = pt3[i];
	}
	box = new BB(min,max);
}
BB* Triangle :: getBox(){
	return box;
}
void Triangle :: setPoint1(float* newPt1){
	pt1 = newPt1;
}
float* Triangle :: getPoint1(){
	return pt1;
}
void Triangle :: setPoint2(float* newPt2){
	pt2 = newPt2;
}
float* Triangle :: getPoint2(){
	return pt2;
}
void Triangle :: setPoint3(float* newPt3){
	pt3 = newPt3;
}
float* Triangle :: getPoint3(){
	return pt3;
}
void Triangle :: setMaterial(int* newMaterial){
	material = newMaterial;
}
int* Triangle :: getMaterial(){
	return material;
}
void Triangle :: printTriangle() const{
	std::cout << "Triangle Object {" << std::endl 
		<< "\tPoint 1: " << printPoint(pt1) << std::endl 
		<< "\tPoint 2: " << printPoint(pt2) << std::endl 
		<< "\tPoint 3: " << printPoint(pt3) << std::endl 
		<< "\tMaterial: " << printPoint(material) << std::endl
		<< "}" << std::endl;
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
//Built using tut from scratchapixel and lecture slides
float Triangle :: intersectRay(Ray *&ray){
	const float * dir = ray->getDirection();

	const float * ori = ray->getOrigin();

	float n_dot_o = dot(ori,normal);
	float n_dot_dir = dot(dir,normal);

	float t = (-n_dot_o + D)/n_dot_dir;

	if(t < eps)
		return -1;

	float point[3] = {0,0,0};
	ray->getPoint(t,point);

	float a1 = getArea(pt3,pt2,point);
	float a2 = getArea(pt3,pt1,point);
	float a3 = getArea(pt2,pt1,point);
	
	float l1 = a1/area;
	float l2 = a2/area;
	float l3 = a3/area;

	float diff = 1 - l1 - l2 - l3; 

	if(diff < eps && diff > -eps)
		return t;
	else
		return -1;

}

float Triangle :: getArea(float* point1, float* point2, float* point3){
	float side1[3] = {0,0,0};
	sub(point2,point1,side1);
	float side2[3] = {0,0,0};
	sub(point3,point1,side2);
	
	float crossRet[3] = {0,0,0};
	cross(side1,side2,crossRet);

	return norm(crossRet)/2;
}

void Triangle :: setNormal(float* ret){
	float side1[3] = {0,0,0};
	sub(pt2,pt1,side1);
	float side2[3] = {0,0,0};
	sub(pt3,pt1,side2);

	cross(side1,side2,ret);

	float retNorm = norm(ret);
	div(ret,retNorm,ret);
}

float* Triangle :: getNormal(){
	return normal;
}