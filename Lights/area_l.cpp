#include <math.h>
#include <iostream>
#include "area_l.h"
#include "Util/func.h"

AreaL :: AreaL(Rect* rect_, float kd_, float illum_){
	rect = rect_;
	center = setCenter();
	Point3D<float> rectNorm = rect->getNormal() * -1;
	center = center + rectNorm;
	kd = kd_;
	illum = illum_;
}

void AreaL :: setRect(Rect* newRect){
	rect = newRect;
}

Rect* AreaL :: getRect(){
	return rect;
}

void AreaL :: setKD(float newKD){
	kd = newKD;
}
float AreaL :: getKD(){
	return kd;
}
void AreaL :: setIllum(float newIllum){
	illum = newIllum;
}
float AreaL :: getIllum(){
	return illum;
}

Point3D<float> AreaL :: getPosition(){
	return center;
}

Point3D<float> AreaL :: getDirectionTo(Point3D<float> pt){
	Point3D<float> ret = pt - center;
	return ret;
}

Point3D<float> AreaL :: setCenter(){
	float x1 = rect->getPoint1()->getX();
	float y1 = rect->getPoint1()->getY();
	float z1 = rect->getPoint1()->getZ();

	float x2 = rect->getPoint2()->getX();
	float y2 = rect->getPoint2()->getY();
	float z2 = rect->getPoint2()->getZ();

	float x3 = rect->getPoint3()->getX();
	float y3 = rect->getPoint3()->getY();
	float z3 = rect->getPoint3()->getZ();

	float x4 = rect->getPoint4()->getX();
	float y4 = rect->getPoint4()->getY();
	float z4 = rect->getPoint4()->getZ();

	Point3D<float> cent;
	cent.setX((x1+x2+x3+x4)/4);
	cent.setY((y1+y2+y3+y4)/4);
	cent.setZ((z1+z2+z3+z4)/4);
	return cent;
}

Point3D<int> AreaL :: phong(Point3D<float> pt, Point3D<float> norm_, Point3D<int> mat, Ray *&ray){
	Point3D<float> ldir = getDirectionTo(pt).normalize();
	float r = pt.distance(center)/500;
	float l_dot_n = ldir.dot(norm_);
	Point3D<float> norm_l_dot_n = norm_ * (2*l_dot_n);
	Point3D<float> reflDir = ldir - norm_l_dot_n;
	Point3D<float> eyeVec = ray->getDirection().normalize();
	// std::cout << pt << std::endl;
	// std::cout << "ldir: " << ldir << " norm_: " << norm_ << " dot: " << sp << std::endl;
	float spec = pow(eyeVec.dot(reflDir)*l_dot_n,32);
	// std::cout << sp << "<-sp" << std::endl;
	// std::cout << spec << "<-spec" << std::endl;
	//diffuse and specular calculation
	float factor = kd*illum*l_dot_n/(r*r);// + spec;
	// std::cout << factor << std::endl;
	if(factor < .1) 
		factor = .1;
	Point3D<int> newMat = mat*factor;
	newMat = newMat.clamp();
	// std::cout << r << " - " << newMat << std::endl;
	// newMat = newMat/(r*r);
	// std::cout << newMat << std::endl;
	return newMat;
}