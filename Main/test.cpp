#include <iostream>
#include "Util/point3D.h"

int main(){
	Point3D<int> point(2,3,4);
	float v = 1.9;
	point = point/v;
	std::cout << point << std::endl;

	return 0;
}