#ifndef DIRECTIONALL_H
#define DIRECTIONALL_H

class DirectionalL{
	private :
		float* direction;
		float kd;
		float illum;

	public : 
		DirectionalL(float* dir, float kd_, float illum_);
		void setDirection(float* newDir);
		float* getDirection();
		void setKD(float newKD);
		float getKD();
		void setIllum(float newIllum);
		float getIllum();

		int* phong(float* norm, int* mat, int* ret);

};

#endif