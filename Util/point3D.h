#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include <math.h>

template <typename T>
class Point3D{
	private :
		T x, y, z;

	public : 
		Point3D(T x_ = 0, T y_ = 0, T z_ = 0){ 
			x = x_;
		    y = y_;
			z = z_;
		}

		Point3D(const Point3D& p){ 
			x = p.x;
		    y = p.y;
			z = p.z;
		}

		int* getColor(){
			int* ret;
			int color[3] = {x,y,z};
			ret = color;
			return ret;
		}
		
		T getX(){
			return x;
		}

		T getY(){
			return y;
		}

		T getZ(){
			return z;
		}

		void setX(T x_){
			x = x_;
		}

		void setY(T y_){
			y = y_;
		}
		void setZ(T z_){
			z = z_;
		}

		void set(T x_ = 0, T y_ = 0, T z_ = 0){
			x = x_;
			y = y_;
			z = z_;
		}

		template <typename U>
		T dot(Point3D<U>& p){
			T dot = 0;
			dot+=(this->x * p.getX());
			dot+=(this->y * p.getY());
			dot+=(this->z * p.getZ());
			return dot;
		}

		template <typename U>
		Point3D cross(Point3D<U>& p){
			Point3D point;
			point.x = this->y*p.getZ() - this->z*p.getY();
			point.y = this->z*p.getX() - this->x*p.getZ();
			point.z = this->x*p.getY() - this->y*p.getX();
			return point;
		}

		template <typename U>
		float distance(Point3D<U>& p){
			float dx = (this->x - p.getX())*(this->x - p.getX());
			float dy = (this->y - p.getY())*(this->y - p.getY());
			float dz = (this->z - p.getZ())*(this->z - p.getZ());
			return sqrt(dx+dy+dz);	
		}

		T getNorm(){
			return sqrt(x * x + y * y + z * z);
		}

		Point3D<T> clamp(){
			T max = std::max(std::max(x,y),z);
			if(max <= 255)
				return *this;
			Point3D<float> point;
			point.setX(1.0*(this->x) / max);
			point.setY(1.0*(this->y) / max);
			point.setZ(1.0*(this->z) / max);
			point = point*255;
			Point3D<int> ret;
			ret.setX(point.getX());
			ret.setY(point.getY());
			ret.setZ(point.getZ());
			return ret;
		}

		void zeroNeg(){
			if(this->x < 0)
				this->x = 0;
			if(this->y < 0)
				this->y = 0;
			if(this->z < 0)
				this->z = 0;
		}

		Point3D<float> normalize(){
			float normal = getNorm();
			Point3D<float> point;
			point.setX(this->x / normal);
			point.setY(this->y / normal);
			point.setZ(this->z / normal);
			return point;
		}

		template <typename U>
		Point3D operator==(Point3D<U>& p){
			return this->x == p.getX() && this->y == p.getY() && this->z == p.getZ();
		}
		
		template <typename U>
		Point3D operator+(Point3D<U>& p){
			Point3D point;
			point.x = this->x + p.getX();
			point.y = this->y + p.getY();
			point.z = this->z + p.getZ();
			return point;
		}
		Point3D operator+(T val){
			Point3D point;
			point.x = this->x + val;
			point.y = this->y + val;
			point.z = this->z + val;
			return point;
		}
		template <typename U>
		Point3D operator-(Point3D<U>& p){
			Point3D point;
			point.x = this->x - p.getX();
			point.y = this->y - p.getY();
			point.z = this->z - p.getZ();
			return point;
		}
		Point3D operator-(T val){
			Point3D point;
			point.x = this->x - val;
			point.y = this->y - val;
			point.z = this->z - val;
			return point;
		}
		template <typename U>
		Point3D operator*(Point3D<U>& p){
			Point3D point;
			point.x = this->x * p.getX();
			point.y = this->y * p.getY();
			point.z = this->z * p.getZ();
			return point;
		}
		template <typename U>
		Point3D operator*(U val){
			Point3D point;
			point.x = this->x * val;
			point.y = this->y * val;
			point.z = this->z * val;
			return point;
		}
		template <typename U>
		Point3D operator/(Point3D<U>& p){
			Point3D point;
			if(p.getX() == 0){
				std::cout << "Divide by zero in x val" << std::endl;
				point.x = this->x;
			}
			else{
				point.x = this->x / p.getX();
			}
			if(p.getY() == 0){
				std::cout << "Divide by zero in y val" << std::endl;
				point.y = this->y;
			}
			else{
				point.y = this->y / p.getY();
			}
			if(p.getZ() == 0){
				std::cout << "Divide by zero in z val" << std::endl;
				point.z = this->z;
			}
			else{
				point.z = this->z / p.getZ();
			}
			return point;
		}
		template <typename U>
		Point3D operator/(U val){
			if(val == 0){
				std::cout << "Divide by zero" << std::endl;
				return *this;
			}
			Point3D point;
			point.x = this->x / val;
			point.y = this->y / val;
			point.z = this->z / val;
			return point;
		}
		
		T operator[](int i){
			switch(i){
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				default:
					return -999;
			}
		}

		friend std::ostream& operator<<(std::ostream &strm, const Point3D<T> &p){
			return strm << "(" << p.x << ", " << p.y << ", " << p.z << ")";
		}

};

#endif