#include <iostream>
#include <string>
#include <math.h>
#include "ray.h"
#include "sphere.h"
#include "func.h"

Sphere :: Sphere(int rad, float* cen, int* mat){
		radius = rad;
		center = cen;
		material = mat;
		eps = .0000001;
}

void Sphere :: setRadius(int newRad){
	radius = newRad;
}

int Sphere :: getRadius(){
	return radius;
}

void Sphere :: setCenter(float* newCenter){
	center = newCenter;
}

float* Sphere :: getCenter(){
	return center;
}

void Sphere :: setMaterial(int* newMaterial){
	material = newMaterial;
}

int* Sphere :: getMaterial(){
	return material;
}

void Sphere :: printSphere() const { 
	std::cout << "Sphere Object {" << std::endl 
		<< "\tRadius: " << radius << std::endl 
		<< "\tCenter: " << printPoint(center) << std::endl 
		<< "\tMaterial: " << printPoint(material) << std::endl
		<< "}" << std::endl;
}

float Sphere :: intersectRay(Ray ray){
	float o_min_c[3] = {0,0,0};
	sub(ray.getOrigin(), center, o_min_c);
	
	float a = dot(ray.getDirection(), ray.getDirection());
	float b = 2*dot(o_min_c, ray.getDirection());
	float c = dot(o_min_c,o_min_c) - radius*radius;

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

float* Sphere :: getNormal(float* pt, float* ret){
	float pt_min_c[3] = {0,0,0};
	sub(pt, center, pt_min_c);

	div(pt_min_c,norm(pt_min_c), ret);

	return ret;
}