#include <iostream>
#include <string>
#include <math.h>
#include "plane.h"
#include "Main/func.h"
#include "Main/ray.h"

Plane :: Plane(float* point_, float* norm, int* mat){
	point = point_;
	normal = norm;
	material = mat;
	eps = .0000001;
}
Plane :: ~Plane(){
	delete [] point;
	delete [] normal;
	delete [] material;
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

//intersection of a Sphere with a ray that returns a time
//based on equations from lecture
float Plane :: intersectRay(Ray *&ray){
	const float * dir = ray->getDirection();

	const float * ori = ray->getOrigin();

	float d_dot_n = dot(dir,normal);
	if(d_dot_n < eps)
		return -1;
	float a_min_o[3] = {0,0,0};
	sub(point,ori,a_min_o);
	float t = dot(a_min_o,normal)/d_dot_n;
	//std::cout << t << std::endl;
	if(t > eps)
		return t;
	return -1;

}