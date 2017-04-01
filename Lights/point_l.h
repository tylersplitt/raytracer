#ifndef POINTL_H
#define POINTL_H

#include "Util/ray.h"
#include "Util/point3D.h"

class PointL{
	private :
		Point3D<float> position;
		float kd;
		float illum;

	public : 
		PointL(Point3D<float> pos, float kd_, float illum_);
		void setPosition(Point3D<float> newDir);
		Point3D<float> getPosition();
		Point3D<float> getDirectionTo(Point3D<float> pt);
		void setKD(float newKD);
		float getKD();
		void setIllum(float newIllum);
		float getIllum();

		Point3D<int> phong(Point3D<float> pt, Point3D<float> norm, Point3D<int> mat, Ray *&ray);

};

#endif