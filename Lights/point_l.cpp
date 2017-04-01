#include <math.h>
#include <iostream>
#include "point_l.h"
#include "Util/func.h"

PointL :: PointL(Point3D<float> pos, float kd_, float illum_){
	position = pos;
	kd = kd_;
	illum = illum_;
}

void PointL :: setPosition(Point3D<float> newPos){
	position = newPos;
}

Point3D<float> PointL :: getPosition(){
	return position;
}

Point3D<float> PointL :: getDirectionTo(Point3D<float> pt){
	Point3D<float> ret = pt - position;
	return ret;
}

void PointL :: setKD(float newKD){
	kd = newKD;
}

float PointL :: getKD(){
	return kd;
}

void PointL :: setIllum(float newIllum){
	illum = newIllum;
}

float PointL :: getIllum(){
	return illum;
}

Point3D<int> PointL :: phong(Point3D<float> pt, Point3D<float> norm_, Point3D<int> mat, Ray *&ray){
	Point3D<float> ldir = getDirectionTo(pt).normalize();
	float r = pt.distance(position)/500;
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