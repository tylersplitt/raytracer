#ifndef AREAL_H
#define AREAL_H

#include "Util/ray.h"
#include "Util/point3D.h"
#include "Shapes/rect.h"

class AreaL{
	private :
		Rect* rect;
		Point3D<float> center;
		float kd;
		float illum;

	public : 
		AreaL(Rect* rect_, float kd_, float illum_);
		void setRect(Rect* newRect);
		Rect* getRect();
		void setKD(float newKD);
		float getKD();
		void setIllum(float newIllum);
		float getIllum();

		Point3D<float> getPosition();
		Point3D<float> setCenter();

		Point3D<float> getDirectionTo(Point3D<float> pt);

		Point3D<int> phong(Point3D<float> pt, Point3D<float> norm, Point3D<int> mat, Ray *&ray);

};

#endif