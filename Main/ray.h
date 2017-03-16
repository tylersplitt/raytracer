#ifndef RAY_H
#define RAY_H

class Ray{
	private :
		const float* origin;
		const float* direction;

	public : 
		Ray(float* ori, float* dir);
		~Ray();
		//void setOrigin(float* newOr);
		const float* getOrigin();
		//void setDirection(float* newDir);
		const float* getDirection();

		void printRay() const;

		float* getPoint(float t,float* ret);

};

#endif