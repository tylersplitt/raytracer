#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "func.h"

int closest(float* t, int n){
	int maxi = 0;
	float maxval = t[0];
	for(int i = 1; i < n; i++){
		if(t[i] > 0 && (t[i] < maxval || maxval < 0)){
			maxval = t[i];
			maxi = i;
		}
	}
	if(maxval < 0)
		return -1;
	else
		return maxi;
}