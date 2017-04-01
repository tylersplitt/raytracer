#include <iostream>
#include <string>
#include <math.h>
#include "sphere.h"
#include "Util/func.h"
#include "Util/ray.h"

Sphere :: Sphere(){

}

Sphere :: Sphere(int rad, Point3D<float>* cen, Point3D<int>* mat){
		radius = rad;
		center = cen;
		material = mat;
		Point3D<float>* min = new Point3D<float>(center->getX() - rad, center->getY() - rad, center->getZ() - rad);
		Point3D<float>* max = new Point3D<float>(center->getX() + rad, center->getY() + rad, center->getZ() + rad);
		box = new BB(min,max);
		eps = .0000001;
}

Sphere :: ~Sphere(){
	delete center;
	delete material;
}

void Sphere :: setSph(int rad, Point3D<float>* cen, Point3D<int>* mat){
		radius = rad;
		center = cen;
		material = mat;
		Point3D<float>* min = new Point3D<float>(center->getX() - rad, center->getY() - rad, center->getZ() - rad);
		Point3D<float>* max = new Point3D<float>(center->getX() + rad, center->getY() + rad, center->getZ() + rad);
		box = new BB(min,max);
		eps = .0000001;
}

BB* Sphere :: getBox(){
	return box;
}

void Sphere :: setRadius(int newRad){
	radius = newRad;
}

int Sphere :: getRadius(){
	return radius;
}

void Sphere :: setCenter(Point3D<float>* newCenter){
	center = newCenter;
}

Point3D<float>* Sphere :: getCenter(){
	return center;
}

void Sphere :: setMaterial(Point3D<int>* newMaterial){
	material = newMaterial;
}

Point3D<int>* Sphere :: getMaterial(){
	return material;
}

void Sphere :: printSphere() const { 
	std::cout << "Sphere Object {" << std::endl 
		<< "\tRadius: " << radius << std::endl 
		<< "\tCenter: " << *center << std::endl 
		<< "\tMaterial: " << *material << std::endl
		<< "}" << std::endl;
}
//intersection of a Sphere with a ray that returns a time
//based on equations from lecture
float Sphere :: intersectRay(Ray *&ray){
	Point3D<float> dir = ray->getDirection();
	Point3D<float> ori = ray->getOrigin();

	Point3D<float> o_min_c = ori - *center;
	
	float a = dir.dot(dir);
	float b = 2*dir.dot(o_min_c);
	float c = o_min_c.dot(o_min_c) - radius*radius;

	float insq = b*b - 4*a*c;
	if(insq < 0.0)
		return -1;
	else{
		float e = sqrt(insq);
		float d = 2*a;
		float t = (-b - e)/d;
		if(t > eps)
			return t;
		t = (-b + e)/d;
		if(t > eps)
			return t;
	}
	return -1;
}

Point3D<float> Sphere :: getNormal(Point3D<float> pt){
	Point3D<float> pt_min_c = *center - pt;// - *center;
	return pt_min_c.normalize();
}