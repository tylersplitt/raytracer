#ifndef BB_H
#define BB_H

#include "Util/ray.h"
#include "Util/point3D.h"

class BB
{
	private :
		Point3D<float>* min;
		Point3D<float>* max;
		float eps;

	public : 
		BB(Point3D<float>* min_, Point3D<float>* max_);
		BB();
		~BB();
		void setBB(Point3D<float>* min_, Point3D<float>* max_);
		void setMin(Point3D<float>* newMin);
		Point3D<float>* getMin();
		float getMinX();
		float getMinY();
		float getMinZ();
		void setMax(Point3D<float>* newMax);
		Point3D<float>* getMax();
		float getMaxX();
		float getMaxY();
		float getMaxZ();
		void printBox() const;
		bool overlap(BB *box);
		bool inBox(Point3D<float> pt);

		float intersectRay(Ray *&ray);


};
#endif