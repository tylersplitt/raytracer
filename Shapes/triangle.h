#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Main/ray.h"
#include "Shapes/BB.h"

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
		BB * box;

	public : 
		Triangle ();
		Triangle(float* pt1_, float* pt2_, float* pt3_, int* mat);
		~Triangle();
		void setTri(float* pt1_, float* pt2_, float* pt3_, int* mat);
		BB* getBox();
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

		float intersectRay(Ray *&ray);
		void setNormal(float* ret);
		float* getNormal();


};
#endif