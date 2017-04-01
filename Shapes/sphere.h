#ifndef SPHERE_H
#define SPHERE_H

#include "Util/ray.h"
#include "Util/point3D.h"
#include "BB.h"

class Sphere
{
	private :
		int radius;
		Point3D<float>* center;
		Point3D<int>* material;
		float eps;
		BB * box;

	public : 
		Sphere(int rad, Point3D<float>* cen, Point3D<int>* mat);
		Sphere();
		~Sphere();
		void setRadius(int newRad);
		void setSph(int rad, Point3D<float>* cen, Point3D<int>* mat);
		BB* getBox();
		int getRadius();
		void setCenter(Point3D<float>* newCenter);
		Point3D<float>* getCenter();
		void setMaterial(Point3D<int>* newMaterial);
		Point3D<int>* getMaterial();
		void printSphere() const;

		float intersectRay(Ray *&ray);
		Point3D<float> getNormal(Point3D<float> pt);


};
#endif