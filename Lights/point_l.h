#ifndef POINTL_H
#define POINTL_H

#include "Main/ray.h"

class PointL{
	private :
		float* position;
		float kd;
		float illum;

	public : 
		PointL(float* pos, float kd_, float illum_);
		void setPosition(float* newDir);
		float* getPosition();
		float* getDirectionTo(float* pt, float* ret);
		void setKD(float newKD);
		float getKD();
		void setIllum(float newIllum);
		float getIllum();

		int* phong(float* pt, float* norm, int* mat, Ray *&ray, int* ret);

};

#endif