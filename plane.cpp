#include <iostream>
#include <string>
#include <math.h>
#include "ray.h"
#include "plane.h"
#include "func.h"

Plane :: Plane(float* point_, float* norm, int* mat){
	point = point_;
	normal = norm;
	material = mat;
	eps = .0000001;
}
void Plane :: setPoint(float* newPoint){
	point = newPoint;
}
float* Plane :: getPoint(){
	return point;
}
void Plane :: setNormal(float* newNormal){
	normal = newNormal;
}
float* Plane :: getNormal(){
	return normal;
}
void Plane :: setMaterial(int* newMaterial){
	material = newMaterial;
}
int* Plane :: getMaterial(){
	return material;
}
void Plane :: printPlane() const{
	std::cout << "Plane Object {" << std::endl 
		<< "\tPoint: " << printPoint(point) << std::endl 
		<< "\tNormal: " << printPoint(normal) << std::endl 
		<< "\tMaterial: " << printPoint(material) << std::endl
		<< "}" << std::endl;
}

float Plane :: intersectRay(Ray ray){
	float d_dot_n = dot(ray.getDirection(),normal);
	if(d_dot_n == 0)
		return -1;
	float a_min_o[3] = {0,0,0};
	sub(point,ray.getOrigin(),a_min_o);
	float t = dot(a_min_o,normal)/d_dot_n;
	if(t > eps)
		return t;
	return -1;

}