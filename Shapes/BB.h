#ifndef BB_H
#define BB_H

#include "Main/ray.h"

class BB
{
	private :
		float* min;
		float* max;
		float eps;

	public : 
		BB(float* min_, float* max_);
		BB();
		~BB();
		void setBB(float* min_, float* max_);
		void setMin(float* newMin);
		float* getMin();
		float getMinX();
		float getMinY();
		float getMinZ();
		void setMax(float* newMax);
		float* getMax();
		float getMaxX();
		float getMaxY();
		float getMaxZ();
		void printBox() const;
		bool overlap(BB *box);
		bool inBox(float* pt);

		float intersectRay(Ray *&ray);


};
#endif