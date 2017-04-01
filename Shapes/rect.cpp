#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include "Util/ray.h"
#include "rect.h"
#include "Util/func.h"

using namespace std;

Rect :: Rect(){

}

Rect :: Rect(Point3D<float>* pt1_, Point3D<float>* pt2_, Point3D<float>* pt3_, Point3D<float>* pt4_, Point3D<int>* mat){
	pt1 = pt1_;
	pt2 = pt2_;
	pt3 = pt3_;
	pt4 = pt4_;
	normal = setNormal();
	D = normal.dot(*pt1);
	area = getArea(*pt1,*pt2,*pt3,*pt4);
	material = mat;
	eps = .000001;
	Point3D<float>* minimum = new Point3D<float>(
									min(min(pt1->getX(),pt2->getX()),min(pt3->getX(),pt4->getX())),
									min(min(pt1->getY(),pt2->getY()),min(pt3->getY(),pt4->getY())),
									min(min(pt1->getZ(),pt2->getZ()),min(pt3->getZ(),pt4->getZ()))
								);
	Point3D<float>* maximum = new Point3D<float>(
									max(max(pt1->getX(),pt2->getX()),max(pt3->getX(),pt4->getX())),
									max(max(pt1->getY(),pt2->getY()),max(pt3->getY(),pt4->getY())),
									max(max(pt1->getZ(),pt2->getZ()),max(pt3->getZ(),pt4->getZ()))
								);
	box = new BB(minimum,maximum);
}
Rect :: ~Rect(){
	delete pt1;
	delete pt2;
	delete pt3;
	delete material;
}
void Rect :: setTri(Point3D<float>* pt1_, Point3D<float>* pt2_, Point3D<float>* pt3_, Point3D<float>* pt4_, Point3D<int>* mat){
	pt1 = pt1_;
	pt2 = pt2_;
	pt3 = pt3_;
	pt4 = pt4_;
	normal = setNormal();
	D = normal.dot(*pt1);
	area = getArea(*pt1,*pt2,*pt3,*pt4);
	material = mat;
	eps = .000001;
	Point3D<float>* minimum = new Point3D<float>(
									min(min(pt1->getX(),pt2->getX()),min(pt3->getX(),pt4->getX())),
									min(min(pt1->getY(),pt2->getY()),min(pt3->getY(),pt4->getY())),
									min(min(pt1->getZ(),pt2->getZ()),min(pt3->getZ(),pt4->getZ()))
								);
	Point3D<float>* maximum = new Point3D<float>(
									max(max(pt1->getX(),pt2->getX()),max(pt3->getX(),pt4->getX())),
									max(max(pt1->getY(),pt2->getY()),max(pt3->getY(),pt4->getY())),
									max(max(pt1->getZ(),pt2->getZ()),max(pt3->getZ(),pt4->getZ()))
								);
	box = new BB(minimum,maximum);
}
BB* Rect :: getBox(){
	return box;
}
void Rect :: setPoint1(Point3D<float>* newPt1){
	pt1 = newPt1;
}
Point3D<float>* Rect :: getPoint1(){
	return pt1;
}
void Rect :: setPoint2(Point3D<float>* newPt2){
	pt2 = newPt2;
}
Point3D<float>* Rect :: getPoint2(){
	return pt2;
}
void Rect :: setPoint3(Point3D<float>* newPt3){
	pt3 = newPt3;
}
Point3D<float>* Rect :: getPoint3(){
	return pt3;
}
void Rect :: setPoint4(Point3D<float>* newPt4){
	pt4 = newPt4;
}
Point3D<float>* Rect :: getPoint4(){
	return pt4;
}
void Rect :: setMaterial(Point3D<int>* newMaterial){
	material = newMaterial;
}
Point3D<int>* Rect :: getMaterial(){
	return material;
}
void Rect :: printRect() const{
	cout << "Rect Object {" << endl 
		<< "\tPoint 1: " << *pt1 << endl 
		<< "\tPoint 2: " << *pt2 << endl 
		<< "\tPoint 3: " << *pt3 << endl 
		<< "\tPoint 4: " << *pt4 << endl 
		<< "\tMaterial: " << *material << endl
		<< "}" << endl;
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-Rect/ray-triangle-intersection-geometric-solution
//Built using tut from scratchapixel and lecture slides
float Rect :: intersectRay(Ray *&ray){
	Point3D<float> dir = ray->getDirection();

	Point3D<float> ori = ray->getOrigin();

	float n_dot_o = ori.dot(normal);
	float n_dot_dir = dir.dot(normal);

	float t = (-n_dot_o + D)/n_dot_dir;

	if(t < eps)
		return -1;

	Point3D<float> point = ray->getPoint(t);

	float a1 = getArea(*pt3,*pt2,point);
	float a2 = getArea(*pt3,*pt4,point);
	float a3 = getArea(*pt2,*pt1,point);
	float a4 = getArea(*pt4,*pt1,point);
	
	float l1 = a1/area;
	float l2 = a2/area;
	float l3 = a3/area;
	float l4 = a4/area;

	float diff = 1 - l1 - l2 - l3 - l4; 

	if(diff < eps && diff > -eps)
		return t;
	else
		return -1;

}

float Rect :: getArea(){
	return area;
}

float Rect :: getArea(Point3D<float> point1, Point3D<float> point2, Point3D<float> point3){
	Point3D<float> side1 = point2 - point1;
	Point3D<float> side2 = point3 - point1;
	Point3D<float> crossRet = side1.cross(side2);

	return crossRet.getNorm()/2;
}

float Rect :: getArea(Point3D<float> point1, Point3D<float> point2, Point3D<float> point3, Point3D<float> point4){
	Point3D<float> side1 = point2 - point1;
	Point3D<float> side2 = point3 - point1;
	Point3D<float> crossRet = side1.cross(side2);

	return crossRet.getNorm();
}

Point3D<float> Rect :: setNormal(){
	Point3D<float> point;
	Point3D<float> side1 = *pt2-*pt1;
	Point3D<float> side2 = *pt3-*pt1;
	point = side1.cross(side2);
	return point.normalize();
}

Point3D<float> Rect :: getNormal(){
	return normal;
}