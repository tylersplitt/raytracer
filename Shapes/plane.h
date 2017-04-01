#ifndef PLANE_H
#define PLANE_H

#include "Util/ray.h"
#include "Util/point3D.h"

class Plane
{
	private :
		Point3D<float>* normal;
		Point3D<float>* point;
		Point3D<int>* material;
		float eps;

	public : 
		Plane(Point3D<float>* point_, Point3D<float>* norm, Point3D<int>* mat);
		Plane();
		~Plane();
		void setPlane(Point3D<float>* point_, Point3D<float>* norm, Point3D<int>* mat);

		void setPoint(Point3D<float>* newPoint);
		Point3D<float>* getPoint();
		void setNormal(Point3D<float>* newNormal);
		Point3D<float>* getNormal();
		void setMaterial(Point3D<int>* newMaterial);
		Point3D<int>* getMaterial();
		void printPlane() const;

		float intersectRay(Ray *&ray);


};
#endif