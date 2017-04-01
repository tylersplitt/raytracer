#ifndef RAY_H
#define RAY_H

#include "point3D.h"

class Ray{
	private :
		Point3D<float> origin;
		Point3D<float> direction;

	public : 
		Ray(Point3D<float> ori, Point3D<float> dir);
		~Ray();
		void setOrigin(Point3D<float> newOr);
		Point3D<float> getOrigin();
		void setDirection(Point3D<float> newDir);
		Point3D<float> getDirection();

		void printRay() const;

		Point3D<float> getPoint(float t);

		float timeToPoint(Point3D<float> pt);


};

#endif