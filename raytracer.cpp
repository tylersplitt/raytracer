#include <iostream>
#include "CImg.h"

using namespace cimg_library;

int main(){
    CImg<float> img(255,255,1,3);
    unsigned char color[] = { 0, 0, 0 };
    for(int i = 0; i < img.height(); i++)
        for(int j = 0; j < img.width(); j++){
            color[0] = i;
            color[1] = j;
            color[2] = 0;
            img.draw_point(i, j, color);
        }
    img.save_png("test.png");
    return 0;
}