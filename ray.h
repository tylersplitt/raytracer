#ifndef RAY_H
#define RAY_H

class Ray{
	private :
		float* origin;
		float* direction;

	public : 
		Ray(float* ori, float* dir);
		void setOrigin(float* newOr);
		float* getOrigin();
		void setDirection(float* newDir);
		float* getDirection();

		float* getPoint(float t,float* ret);

};

#endif