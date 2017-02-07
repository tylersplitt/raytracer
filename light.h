#ifndef LIGHT_H
#define LIGHT_H

class Light{
	private :
		float* direction;
		float kd;
		float illum;

	public : 
		Light(float* dir, float kd_, float illum_);
		void setDirection(float* newDir);
		float* getDirection();
		void setKD(float newKD);
		float getKD();
		void setIllum(float newIllum);
		float getIllum();

		int* phong(float* pt, float* norm, int* mat, int* ret);

};

#endif