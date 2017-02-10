#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "ray.h"

class Triangle
{
	private :
		float* pt1;
		float* pt2;
		float* pt3;
		float normal[3];
		float D;
		float area;
		int* material;
		float eps;

	public : 
		Triangle(float* pt1_, float* pt2_, float* pt3_, int* mat);
		void setPoint1(float* newPt1);
		float* getPoint1();
		void setPoint2(float* newPt2);
		float* getPoint2();
		void setPoint3(float* newPt3);
		float* getPoint3();
		void setMaterial(int* newMaterial);
		int* getMaterial();
		float getArea(float* point1,float* point2,float* point3);
		void printTriangle() const;

		float intersectRay(Ray ray);
		void setNormal(float* ret);
		float* getNormal();


};
#endif