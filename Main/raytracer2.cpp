#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "CImg.h"
#include "Shapes/sphere.h"
#include "Shapes/plane.h"
#include "Shapes/triangle.h"
#include "Shapes/BB.h"
#include "Shapes/grid.h"
#include "ray.h"
#include "Lights/directional_l.h"
#include "Lights/point_l.h"
#include "func.h"

using namespace cimg_library;

/**
    Spheres ray tracer
    MP2 Google doc link: https://docs.google.com/document/d/1INN31AYnI4K1SPYwHzv-urN0GGfs8DJrewOSgw2h97k/edit?usp=sharing
**/
int main(){
    //Whether or not to use the regular grid acceleration
    int acc = 0;

    //Camera
    float* cam = new float[3];
    cam[0] = 0;
    cam[1] = 0;
    cam[2] = 1000;

    //Grid init
    int boxWidth = 512;
    float cellWidth = 64;
    const int numSpheres = 100;
    int sphRad = 30;
    float minx = -(boxWidth/2);
    float miny = -(boxWidth/2);
    float minz = -boxWidth; 
    std::cout << "Creating grid" << std::endl;
    Grid* grid = new Grid(minx, miny, minz, boxWidth, cellWidth);
    Sphere * spheres = new Sphere[numSpheres];
    std::cout << "Creating spheres" << std::endl;
    //Creates numSpheres spheres within the box specifications
    for(int i = 0; i < numSpheres; i++){
        float* cent = new float[3];
        cent[0] = rand() % (boxWidth-sphRad) - (boxWidth-sphRad)/2;
        cent[1] = rand() % (boxWidth-sphRad) - (boxWidth-sphRad)/2;
        cent[2] = -(rand() % (boxWidth-sphRad));
        int* mat = new int[3];
        mat[0] = rand() % 236 + 20;
        mat[1] = rand() % 236 + 20;
        mat[2] = rand() % 236 + 20;
        spheres[i].setSph(sphRad,cent,mat);
    }
    std::cout << "Finished making spheres" << std::endl;
    int curInd = 0;
    std::vector<int>* gridCells = grid->getGridCells();
    int * counts = grid->getCounts();
    std::cout << "Starting to fill grid" << std::endl;
    int imin = grid->getMinX();
    int imax = grid->getMaxX();
    int jmin = grid->getMinY();
    int jmax = grid->getMaxY();
    int kmin = grid->getMinZ();
    int kmax = grid->getMaxZ();
    //Adds spheres to the grid using the bounding boxes of the spheres
    for(int i = imin; i < imax; i+=cellWidth){
        for(int j = jmin; j < jmax; j+=cellWidth){
            for(int k = kmin; k < kmax; k+=cellWidth){
                float* minC = new float[3];
                minC[0] = i;
                minC[1] = j;
                minC[2] = k;
                float* maxC = new float[3];
                maxC[0] = i + cellWidth;
                maxC[1] = j + cellWidth;
                maxC[2] = k + cellWidth;
                BB curCell(minC, maxC);
                for(int x = 0; x < numSpheres; x++){
                    if(curCell.overlap(spheres[x].getBox())){
                        gridCells[curInd].push_back(x);
                        counts[curInd]++;
                    }
                }
                curInd++;
            }
        }
    }
    std::cout << "Finished filling grid" << std::endl;

    //light constructor
    float lpos[3] = {0, -200, 100};
    float kd = .75;
    float illum = 1.0;
    PointL light(lpos,kd,illum);

    //background color
    int background[3] = {0,0,0};
    //image creation
    CImg<float> img(512,512,1,3);
    std::cout << "Traversing image" << std::endl;
    for(int i = 0; i < img.height(); i++)
        for(int j = 0; j < img.width(); j++){
            int* drawColor = new int[3];
            float* hitPoint = new float[3];
            //based of code seen in class found at https://github.com/shaffer1/UIllinois_Rendering
            float pixX = (i - img.height()/2.0+.5);
            float pixY = (j - img.width()/2.0+.5);
            float pixCenter[3] = {pixX, pixY, 0};
            //perspective projection calculation using a camera behind the image
            //ray constructor
            float* rayOr = new float[3];
            rayOr[0] = cam[0];
            rayOr[1] = cam[1];
            rayOr[2] = cam[2];
            float* raydir = new float[3];
            raydir[0] = pixCenter[0] - rayOr[0];
            raydir[1] = pixCenter[1] - rayOr[1];
            raydir[2] = pixCenter[2] - rayOr[2];
            Ray* ray = new Ray(rayOr, raydir);

            //if acceleration was toggled on
            if(acc){
                //drawing variables
                int ct = -1;
                float drawT = -1;
                int drawX = -1;
                //gets starting cell of grid
                int curCell = grid->getFirstCell(ray);
                while(ct == -1 && curCell > 0){
                    ct = -1;
                    //gets #spheres in that cell
                    int count = counts[curCell];
                    float* t = new float[count];
                    //checks if any of them intersect
                    for(int x = 0; x < count; x++){
                        t[x] = spheres[gridCells[curCell][x]].intersectRay(ray);
                    }
                    //gets the closest if any are in the cell
                    if(count > 0)
                        ct = closest(t,count);
                    //if there is no hit, it traverses to the next cell
                    if(ct == -1)
                        curCell = grid->getNextCell(ray,curCell);
                    else{
                        //sets the draw t value and index of the sphere that was hit
                        drawT = t[ct];
                        drawX = gridCells[curCell][ct];
                    }
                    delete [] t;
                }
                //draws the sphere
                if(ct != -1){
                    ray->getPoint(drawT,hitPoint);
                    float sphNorm[3] = {0,0,0};
                    spheres[drawX].getNormal(hitPoint,sphNorm);
                    light.phong(hitPoint,sphNorm,spheres[drawX].getMaterial(),ray,drawColor);
                    img.draw_point(i, j, drawColor);
                }
                //if no shapes are hit draw the background
                else{
                    img.draw_point(i, j, background);
                }
            }
            //non accelerated code
            else{
                int ct = -1;
                float * t = new float[numSpheres];
                //checks all the spheres for the closest one
                for(int x = 0; x < numSpheres; x++){
                    t[x] = spheres[x].intersectRay(ray);
                }
                ct = closest(t,numSpheres);
                if(ct != -1){
                    ray->getPoint(t[ct],hitPoint);
                    float sphNorm[3] = {0,0,0};
                    spheres[ct].getNormal(hitPoint,sphNorm);
                    light.phong(hitPoint, sphNorm,spheres[ct].getMaterial(),ray,drawColor);
                    //shadow calculation
                    float * shadowDir = new float[3];
                    sub(light.getPosition(),hitPoint,shadowDir);
                    Ray* shadowRay = new Ray(hitPoint, shadowDir);
                    float* t = new float[numSpheres];
                    for(int x = 0; x < numSpheres; x++){
                        if(x != ct)
                            t[x] = spheres[x].intersectRay(shadowRay);
                    }
                    float st = closest(t,numSpheres);
                    if(st > 0)
                        img.draw_point(i, j, background);
                    else
                        img.draw_point(i, j, drawColor);
                    delete [] t;
                }
                //if no shapes are hit draw the background
                else{
                    img.draw_point(i, j, background);
                }
                delete [] t;
            }
            delete [] drawColor;
            delete [] hitPoint;
            delete ray;
        }
    delete [] cam;
    img.save_png("test2.png");
    return 0;
}