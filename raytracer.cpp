#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "CImg.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "ray.h"
#include "light.h"
#include "func.h"

using namespace cimg_library;

int main(){
    //perspective camera on and off
    int pers = 0;
    float cam[3] = {0,0,500};

    //multi-jittering on and off
    int jitt = 0;

    //sphere 1 constructor
    float sphCent1[3] = {0,0,-200};
    int sphMat1[3] = {135,25,130};
    Sphere sph1(50,sphCent1,sphMat1);

    sph1.printSphere();

    //sphere 2 constructor
    float sphCent2[3] = {-50, -150, -100};
    int sphMat2[3] = {50, 145, 265};
    Sphere sph2(100, sphCent2, sphMat2);

    sph2.printSphere();

    //plane constructor
    float point[3] = {0,249,0};
    float norm[3] = {0,-1,.1};
    int planeMat[3] = {0,0,255};
    Plane plane(point,norm,planeMat);

    plane.printPlane();

    //triangle constructor
    float triPoint1[3] = {0,0,-400};
    float triPoint2[3] = {200,150,-10};
    float triPoint3[3] = {-100,200,-200};
    int triMat[3] = {255,0,0};
    Triangle triangle(triPoint1,triPoint2,triPoint3,triMat);

    triangle.printTriangle();

    //second triangle constructor
    float tri2Point1[3] = {-190,80,-30};
    float tri2Point2[3] = {-100,-50,-50};
    float tri2Point3[3] = {-150,200,-200};
    int tri2Mat[3] = {230,80,30};
    Triangle triangle2(tri2Point1,tri2Point2,tri2Point3,tri2Mat);

    triangle2.printTriangle();

    //ray constructor
    float dir[3] = {0,0,-1};
    float center[3] = {0,0,0};
    Ray ray(center,dir);

    //light constructor
    float ldir[3] = {0,0,1};
    float kd = .75;
    float illum = 1.0;
    Light light(ldir,kd,illum);

    //background color
    int background[3] = {0,0,0};
    //image creation
    CImg<float> img(512,512,1,3);
    //increase pixel size by increasing step value
    int step = 1;
    int rts = sqrt(step);
    for(int i = step/2; i < img.height(); i+=step)
        for(int j = step/2; j < img.width(); j+=step){
            //mulit-jittering calculation
            if(jitt == 1){
                int avgColor[3] = {0,0,0};
                for(int x = i-step/2+rts/2; x < i+step/2; x+=rts){
                    for(int y = j-step/2+rts/2; y < j+step/2; y+=rts){
                        //sqrt(step) is used to get a random sample in a fine grid and to get a jittered sample
                        //in each pixel. 
                        float jittOrigin[3] = {rand()%rts+x-rts/2 -img.height()/2, rand()%rts+y-rts/2 - img.width()/2, 0};
                        ray.setOrigin(jittOrigin);
                        float t = sph1.intersectRay(ray);
                        int tempColor[3] = {0,0,0};
                        //Only jittered with a sphere so it was either the sphere or background
                        if(t > 0)
                            copy(sph1.getMaterial(),tempColor);
                        else 
                            copy(background,tempColor);
                        //average jittered pixel colors to get better color
                        mult(tempColor, 1/(step*1.0), tempColor);
                        add(avgColor, tempColor, avgColor);
                    }
                }
                //drawing the avg color on the pixel
                for(int m = i-step/2; m < i+step/2; m++){
                    for(int n = j-step/2; n < j+step/2; n++){
                        img.draw_point(m, n, avgColor);
                    }
                }    
            }
            else{
                //not jittered drawing
                //based of code seen in class found at https://github.com/shaffer1/UIllinois_Rendering
                float pixCenter[3] = {(i - img.height()/2+.5),(j - img.width()/2+.5), 0};
                //perspective projection calculation using a camera behind the image
                if(pers == 1){
                    ray.setOrigin(cam);
                    float newDir[3] = {0,0,0};
                    sub(pixCenter,cam,newDir); 
                    ray.setDirection(newDir);
                }
                //orthographic
                else
                    ray.setOrigin(pixCenter);

                //Increase shapes and add the intersection to increase shapes in view
                int shapes = 5;
                float t[shapes];
                t[0] = sph1.intersectRay(ray);
                t[1] = plane.intersectRay(ray);
                t[2] = triangle.intersectRay(ray);
                t[3] = sph2.intersectRay(ray);
                t[4] = triangle2.intersectRay(ray);
                int ct = closest(t,shapes);
                if(ct == 4){
                    float pointOnTri[3] = {0,0,0};
                    ray.getPoint(t[4],pointOnTri);
                    int phColor[3] = {0,0,0};
                    //used to calculate surface light using basic phong shading using normal and the point
                    light.phong(pointOnTri,triangle2.getNormal(),triangle2.getMaterial(),phColor);
                    img.draw_point(i, j, phColor);
                }
                else if(ct == 3){
                    float point[3] = {0,0,0};
                    ray.getPoint(t[3],point);
                    float shapeNormal[3] = {0,0,0};
                    sph2.getNormal(point, shapeNormal);
                    int phColor[3] = {0,0,0};
                    light.phong(point,shapeNormal,sph2.getMaterial(),phColor);
                    img.draw_point(i, j, phColor);
                }
                else if(ct == 2){
                    float pointOnTri[3] = {0,0,0};
                    ray.getPoint(t[2],pointOnTri);
                    int phColor[3] = {0,0,0};
                    light.phong(pointOnTri,triangle.getNormal(),triangle.getMaterial(),phColor);
                    img.draw_point(i, j, phColor);
                }
                else if(ct == 1){
                    float pointOnPlane[3] = {0,0,0};
                    ray.getPoint(t[1],pointOnPlane);
                    int phColor[3] = {0,0,0};
                    light.phong(pointOnPlane,plane.getNormal(),plane.getMaterial(),phColor);
                    img.draw_point(i, j, phColor);
                }
                else if(ct == 0){
                    float pointOnSphere[3] = {0,0,0};
                    ray.getPoint(t[0],pointOnSphere);
                    float sphNormal[3] = {0,0,0};
                    sph1.getNormal(pointOnSphere, sphNormal);
                    int phColor[3] = {0,0,0};
                    light.phong(pointOnSphere,sphNormal,sph1.getMaterial(),phColor);
                    for(int x = i-step/2; x < i+step/2; x++){
                        for(int y = j-step/2; y < j+step/2; y++){
                            if(jitt == 1)
                                img.draw_point(x, y, sph1.getMaterial());
                        }                    
                    }
                    img.draw_point(i, j, phColor);
                }
                //if no shapes are hit draw the background
                else
                    img.draw_point(i, j, background);
            }
        }
    img.save_png("test.png");
    return 0;
}