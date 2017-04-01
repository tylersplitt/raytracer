#ifndef RECT_H
#define RECT_H

#include "Util/ray.h"
#include "Util/point3D.h"
#include "BB.h"

class Rect
{
	private :
		Point3D<float>* pt1;
		Point3D<float>* pt2;
		Point3D<float>* pt3;
		Point3D<float>* pt4;
		Point3D<float> normal;
		float D;
		float area;
		Point3D<int>* material;
		float eps;
		BB * box;

	public : 
		Rect ();
		Rect(Point3D<float>* pt1_, Point3D<float>* pt2_, Point3D<float>* pt3_, Point3D<float>* pt4_, Point3D<int>* mat);
		~Rect();
		void setTri(Point3D<float>* pt1_, Point3D<float>* pt2_, Point3D<float>* pt3_, Point3D<float>* pt4_, Point3D<int>* mat);
		BB* getBox();
		void setPoint1(Point3D<float>* newPt1);
		Point3D<float>* getPoint1();
		void setPoint2(Point3D<float>* newPt2);
		Point3D<float>* getPoint2();
		void setPoint3(Point3D<float>* newPt3);
		Point3D<float>* getPoint3();
		void setPoint4(Point3D<float>* newPt4);
		Point3D<float>* getPoint4();
		void setMaterial(Point3D<int>* newMaterial);
		Point3D<int>* getMaterial();
		float getArea();
		float getArea(Point3D<float>  point1,Point3D<float> point2,Point3D<float> point3);
		float getArea(Point3D<float>  point1,Point3D<float> point2,Point3D<float> point3,Point3D<float> point4);
		void printRect() const;

		float intersectRay(Ray *&ray);
		Point3D<float> setNormal();
		Point3D<float> getNormal();


};
#endif