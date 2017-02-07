#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"

class Sphere
{
	private :
		int radius;
		float* center;
		int* material;
		float eps;

	public : 
		Sphere(int rad, float* cen, int* mat);
		void setRadius(int newRad);
		int getRadius();
		void setCenter(float* newCenter);
		float* getCenter();
		void setMaterial(int* newMaterial);
		int* getMaterial();
		void printSphere() const;

		float intersectRay(Ray ray);
		float* getNormal(float* pt, float* ret);


};
#endif