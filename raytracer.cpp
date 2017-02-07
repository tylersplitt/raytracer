#include <iostream>
#include <math.h>
#include "CImg.h"
#include "sphere.h"
#include "plane.h"
#include "ray.h"
#include "light.h"
#include "func.h"

using namespace cimg_library;

int main(){
    float center[3] = {0,10,-500};
    int material[3] = {135,25,130};
    Sphere sph(200,center,material);

    sph.printSphere();

    float point[3] = {0,0,-500};
    float rt2 = sqrt(2);
    float norm[3] = {0,-1,.35};
    int planeMat[3] = {0,0,255};
    Plane plane(point,norm,planeMat);

    plane.printPlane();

    float dir[3] = {0,0,-1};
    Ray ray(center,dir);

    float ldir[3] = {0,0,1};
    float kd = .75;
    float illum = 1.0;
    Light light(ldir,kd,illum);

    float black[3] = {0,0,0};
    CImg<float> img(500,500,1,3);
    for(int i = 0; i < img.height(); i++)
        for(int j = 0; j < img.width(); j++){
            float pixCenter[3] = {(i - img.height()/2+.5),(j - img.width()/2+.5), 0};
            ray.setOrigin(pixCenter);
            float t = sph.intersectRay(ray);
            float pt = plane.intersectRay(ray);
            if(pt > 0 && (t < 0 || pt < t)){
                float pointOnPlane[3] = {0,0,0};
                ray.getPoint(t,pointOnPlane);
                int phColor[3] = {0,0,0};
                light.phong(pointOnPlane,plane.getNormal(),plane.getMaterial(),phColor);
                img.draw_point(i, j, phColor);
            }
            else if(t > 0){
                float pointOnSphere[3] = {0,0,0};
                ray.getPoint(t,pointOnSphere);
                float sphNormal[3] = {0,0,0};
                sph.getNormal(pointOnSphere, sphNormal);
                int phColor[3] = {0,0,0};
                light.phong(pointOnSphere,sphNormal,sph.getMaterial(),phColor);
                img.draw_point(i, j, phColor);
            }
            else
                img.draw_point(i, j, black);
        }
    img.save_png("test.png");
    return 0;
}