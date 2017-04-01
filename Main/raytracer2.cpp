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
#include "Util/ray.h"
#include "Lights/directional_l.h"
#include "Lights/point_l.h"
#include "Util/func.h"
#include "Util/point3D.h"

using namespace std;

/**
    Spheres ray tracer
    MP2 Google doc link: https://docs.google.com/document/d/1INN31AYnI4K1SPYwHzv-urN0GGfs8DJrewOSgw2h97k/edit?usp=sharing
**/
int main(){
    //Whether or not to use the regular grid acceleration
    int acc = 1;

    //Camera
    Point3D<float> cam(0,0,1000);


    //light constructor
    Point3D<float> lpos(0, -200, 100);
    float kd = .75;
    float illum = 1.0;
    PointL light(lpos,kd,illum);

    //Grid init
    int boxWidth = 512;
    float cellWidth = 64;
    const int numSpheres = 100;
    int sphRad = 30;
    float minx = -(boxWidth/2);
    float miny = -(boxWidth/2);
    float minz = -boxWidth; 
    cout << "Creating grid" << endl;
    Grid* grid = new Grid(minx, miny, minz, boxWidth, cellWidth);
    Sphere * spheres = new Sphere[numSpheres];
    cout << "Creating spheres" << endl;
    //Creates numSpheres spheres within the box specifications
    for(int i = 0; i < numSpheres; i++){
        Point3D<float>* cent = new Point3D<float>();
        cent->setX(rand() % (boxWidth-sphRad) - (boxWidth-sphRad)/2);
        cent->setY(rand() % (boxWidth-sphRad) - (boxWidth-sphRad)/2);
        cent->setZ(-(rand() % (boxWidth-sphRad)));
        Point3D<int>* mat = new Point3D<int>(rand() % 236 + 20,rand() % 236 + 20,rand() % 236 + 20);
        spheres[i].setSph(sphRad,cent,mat);
    }
    cout << "Finished making spheres" << endl;
    int curInd = 0;
    vector<int>* gridCells = grid->getGridCells();
    int * counts = grid->getCounts();
    cout << "Starting to fill grid" << endl;
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
                Point3D<float>* minC = new Point3D<float>(i,j,k);
                Point3D<float>* maxC = new Point3D<float>(i+cellWidth,j+cellWidth,k+cellWidth);
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
    cout << "Finished filling grid" << endl;

    //background color
    int background[3] = {0,0,0};
    //image creation
    cimg_library::CImg<float> img(512,512,1,3);
    cout << "Traversing image" << endl;
    for(int i = 0; i < img.height(); i++)
        for(int j = 0; j < img.width(); j++){
            Point3D<int> drawColor;
            Point3D<float> hitPoint;
            //based of code seen in class found at https://github.com/shaffer1/UIllinois_Rendering
            float pixX = (i - img.height()/2.0+.5);
            float pixY = (j - img.width()/2.0+.5);
            Point3D<float> pixCenter(pixX, pixY, 0);
            //perspective projection calculation using a camera behind the image
            //ray constructor
            Point3D<float> rayOr(cam);
            Point3D<float> rayDir;
            rayDir.setX(pixCenter[0] - rayOr.getX());
            rayDir.setY(pixCenter[1] - rayOr.getY());
            rayDir.setZ(pixCenter[2] - rayOr.getZ());
            Ray* ray = new Ray(rayOr, rayDir);
            // ray->printRay();

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
                    hitPoint = ray->getPoint(drawT);
                    Point3D<float> sphNorm = spheres[drawX].getNormal(hitPoint);
                    Point3D<int>* sphMat = spheres[drawX].getMaterial();
                    drawColor = light.phong(hitPoint,sphNorm,*sphMat,ray);
                    int col[3] = {drawColor.getX(),drawColor.getY(),drawColor.getZ()};
                    img.draw_point(i, j, col);
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
                    hitPoint = ray->getPoint(t[ct]);
                    Point3D<float> sphNorm = spheres[ct].getNormal(hitPoint);
                    Point3D<int>* sphMat = spheres[ct].getMaterial();
                    drawColor = light.phong(hitPoint, sphNorm,*sphMat,ray);
                    // shadow calculation
                    Point3D<float> shadowDir;
                    shadowDir = light.getPosition() - hitPoint;
                    Ray* shadowRay = new Ray(hitPoint, shadowDir);
                    float* t = new float[numSpheres];
                    for(int x = 0; x < numSpheres; x++){
                        if(x != ct)
                            t[x] = spheres[x].intersectRay(shadowRay);
                    }
                    float st = closest(t,numSpheres);
                    if(st > 0)
                        img.draw_point(i, j, background);
                    else{
                        int col[3] = {drawColor.getX(),drawColor.getY(),drawColor.getZ()};
                        img.draw_point(i, j, col);
                    }
                    delete [] t;
                }
                //if no shapes are hit draw the background
                else{
                    img.draw_point(i, j, background);
                }
                delete [] t;
            }
            delete ray;
        }
    img.save_png("Pics/test2.png");
    return 0;
}