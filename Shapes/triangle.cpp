#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include "Util/ray.h"
#include "triangle.h"
#include "Util/func.h"

using namespace std;

Triangle :: Triangle(){

}

Triangle :: Triangle(Point3D<float>* pt1_, Point3D<float>* pt2_, Point3D<float>* pt3_, Point3D<int>* mat){
	pt1 = pt1_;
	pt2 = pt2_;
	pt3 = pt3_;
	normal = setNormal();
	D = normal.dot(*pt1);
	area = getArea(*pt1,*pt2,*pt3);
	material = mat;
	eps = .000001;
	Point3D<float>* minimum = new Point3D<float>(
									min(min(pt1->getX(),pt2->getX()),pt3->getX()),
									min(min(pt1->getY(),pt2->getY()),pt3->getY()),
									min(min(pt1->getZ(),pt2->getZ()),pt3->getZ())
								);
	Point3D<float>* maximum = new Point3D<float>(
									max(max(pt1->getX(),pt2->getX()),pt3->getX()),
									max(max(pt1->getY(),pt2->getY()),pt3->getY()),
									max(max(pt1->getZ(),pt2->getZ()),pt3->getZ())
								);
	box = new BB(minimum,maximum);
}
Triangle :: ~Triangle(){
	delete pt1;
	delete pt2;
	delete pt3;
	delete material;
}
void Triangle :: setTri(Point3D<float>* pt1_, Point3D<float>* pt2_, Point3D<float>* pt3_, Point3D<int>* mat){
	pt1 = pt1_;
	pt2 = pt2_;
	pt3 = pt3_;
	normal = setNormal();
	D = normal.dot(*pt1);
	area = getArea(*pt1,*pt2,*pt3);
	material = mat;
	eps = .000001;
	Point3D<float>* minimum = new Point3D<float>(
									min(min(pt1->getX(),pt2->getX()),pt3->getX()),
									min(min(pt1->getY(),pt2->getY()),pt3->getY()),
									min(min(pt1->getZ(),pt2->getZ()),pt3->getZ())
								);
	Point3D<float>* maximum = new Point3D<float>(
									max(max(pt1->getX(),pt2->getX()),pt3->getX()),
									max(max(pt1->getY(),pt2->getY()),pt3->getY()),
									max(max(pt1->getZ(),pt2->getZ()),pt3->getZ())
								);
	box = new BB(minimum,maximum);
}
BB* Triangle :: getBox(){
	return box;
}
void Triangle :: setPoint1(Point3D<float>* newPt1){
	pt1 = newPt1;
}
Point3D<float>* Triangle :: getPoint1(){
	return pt1;
}
void Triangle :: setPoint2(Point3D<float>* newPt2){
	pt2 = newPt2;
}
Point3D<float>* Triangle :: getPoint2(){
	return pt2;
}
void Triangle :: setPoint3(Point3D<float>* newPt3){
	pt3 = newPt3;
}
Point3D<float>* Triangle :: getPoint3(){
	return pt3;
}
void Triangle :: setMaterial(Point3D<int>* newMaterial){
	material = newMaterial;
}
Point3D<int>* Triangle :: getMaterial(){
	return material;
}
void Triangle :: printTriangle() const{
	cout << "Triangle Object {" << endl 
		<< "\tPoint 1: " << *pt1 << endl 
		<< "\tPoint 2: " << *pt2 << endl 
		<< "\tPoint 3: " << *pt3 << endl 
		<< "\tMaterial: " << *material << endl
		<< "}" << endl;
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
//Built using tut from scratchapixel and lecture slides
float Triangle :: intersectRay(Ray *&ray){
	Point3D<float> dir = ray->getDirection();

	Point3D<float> ori = ray->getOrigin();

	float n_dot_o = ori.dot(normal);
	float n_dot_dir = dir.dot(normal);

	float t = (-n_dot_o + D)/n_dot_dir;

	if(t < eps)
		return -1;

	Point3D<float> point = ray->getPoint(t);

	float a1 = getArea(*pt3,*pt2,point);
	float a2 = getArea(*pt3,*pt1,point);
	float a3 = getArea(*pt2,*pt1,point);
	
	float l1 = a1/area;
	float l2 = a2/area;
	float l3 = a3/area;

	float diff = 1 - l1 - l2 - l3; 

	if(diff < eps && diff > -eps)
		return t;
	else
		return -1;

}

float Triangle :: getArea(Point3D<float> point1, Point3D<float> point2, Point3D<float> point3){
	Point3D<float> side1 = point2 - point1;
	Point3D<float> side2 = point3 - point1;
	Point3D<float> crossRet = side1.cross(side2);

	return crossRet.getNorm()/2;
}

Point3D<float> Triangle :: setNormal(){
	Point3D<float> point;
	Point3D<float> side1 = *pt2-*pt1;
	Point3D<float> side2 = *pt3-*pt1;
	point = side1.cross(side2);
	return point.normalize();
}

Point3D<float> Triangle :: getNormal(){
	return normal;
}