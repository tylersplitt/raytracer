#include <iostream>
#include <string>
#include <math.h>
#include "sphere.h"
#include "Main/func.h"
#include "Main/ray.h"

Sphere :: Sphere(){

}

Sphere :: Sphere(int rad, float* cen, int* mat){
		radius = rad;
		center = cen;
		material = mat;
		float min[3] = {0,0,0};
		float max[3] = {0,0,0};
		for(int i = 0; i < 3; i++){
			min[i] = center[i] - rad;
			max[i] = center[i] + rad;
		}
		std::cout << printPoint(min) << std::endl;
		box = new BB(min,max);
		eps = .0000001;
}

Sphere :: ~Sphere(){
	delete [] center;
	delete [] material;
}

void Sphere :: setSph(int rad, float* cen, int* mat){
		radius = rad;
		center = cen;
		material = mat;
		float * min = new float[3];
		float * max = new float[3];
		for(int i = 0; i < 3; i++){
			min[i] = center[i] - rad;
			max[i] = center[i] + rad;
		}
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
//intersection of a Sphere with a ray that returns a time
//based on equations from lecture
float Sphere :: intersectRay(Ray *&ray){
	// return box->intersectRay(ray);
	const float * dir = ray->getDirection();

	const float * ori = ray->getOrigin();

	float o_min_c[3] = {0,0,0};
	sub(ori, center, o_min_c);
	
	float a = dot(dir, dir);
	float b = 2*dot(dir, o_min_c);
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