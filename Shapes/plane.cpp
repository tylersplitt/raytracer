#include <iostream>
#include <string>
#include <math.h>
#include "plane.h"
#include "Util/func.h"
#include "Util/ray.h"

Plane :: Plane(Point3D<float>* point_, Point3D<float>* norm, Point3D<int>* mat){
	point = point_;
	normal = norm;
	material = mat;
	eps = .0000001;
}
Plane :: Plane(){}

Plane :: ~Plane(){
	delete point;
	delete normal;
	delete material;
}

void Plane :: setPlane(Point3D<float>* point_, Point3D<float>* norm, Point3D<int>* mat){
	point = point_;
	normal = norm;
	material = mat;
	eps = .0000001;
}

void Plane :: setPoint(Point3D<float>* newPoint){
	point = newPoint;
}
Point3D<float>* Plane :: getPoint(){
	return point;
}
void Plane :: setNormal(Point3D<float>* newNormal){
	normal = newNormal;
}
Point3D<float>* Plane :: getNormal(){
	return normal;
}
void Plane :: setMaterial(Point3D<int>* newMaterial){
	material = newMaterial;
}
Point3D<int>* Plane :: getMaterial(){
	return material;
}
void Plane :: printPlane() const{
	std::cout << "Plane Object {" << std::endl 
		<< "\tPoint: " << *point << std::endl 
		<< "\tNormal: " << *normal << std::endl 
		<< "\tMaterial: " << *material << std::endl
		<< "}" << std::endl;
}

float Plane :: intersectRay(Ray *&ray){
	Point3D<float> dir = ray->getDirection();
	Point3D<float> ori = ray->getOrigin();

	float d_dot_n = dir.dot(*normal);
	if(d_dot_n < eps)
		return -1;
	Point3D<float> a_min_o = *point-ori;
	float t = a_min_o.dot(*normal)/d_dot_n;
	if(t > eps)
		return t;
	return -1;

}