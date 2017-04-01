#ifndef DIRECTIONALL_H
#define DIRECTIONALL_H

#include "Util/point3D.h"

class DirectionalL{
	private :
		Point3D<float> direction;
		float kd;
		float illum;

	public : 
		DirectionalL(Point3D<float> dir, float kd_, float illum_);
		void setDirection(Point3D<float> newDir);
		Point3D<float> getDirection();
		void setKD(float newKD);
		float getKD();
		void setIllum(float newIllum);
		float getIllum();

		Point3D<int> phong(Point3D<float> norm, Point3D<int> mat);

};

#endif