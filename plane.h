#ifndef PLANE_H
#define PLANE_H

#include "ray.h"

class Plane
{
	private :
		float* normal;
		float* point;
		int* material;
		float eps;

	public : 
		Plane(float* point_, float* norm, int* mat);
		void setPoint(float* newPoint);
		float* getPoint();
		void setNormal(float* newNormal);
		float* getNormal();
		void setMaterial(int* newMaterial);
		int* getMaterial();
		void printPlane() const;

		float intersectRay(Ray ray);


};
#endif