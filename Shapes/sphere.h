#ifndef SPHERE_H
#define SPHERE_H

#include "Main/ray.h"
#include "Shapes/BB.h"

class Sphere
{
	private :
		int radius;
		float* center;
		int* material;
		float eps;
		BB * box;

	public : 
		Sphere(int rad, float* cen, int* mat);
		Sphere();
		~Sphere();
		void setRadius(int newRad);
		void setSph(int rad, float* cen, int* mat);
		BB* getBox();
		int getRadius();
		void setCenter(float* newCenter);
		float* getCenter();
		void setMaterial(int* newMaterial);
		int* getMaterial();
		void printSphere() const;

		float intersectRay(Ray *&ray);
		float* getNormal(float* pt, float* ret);


};
#endif