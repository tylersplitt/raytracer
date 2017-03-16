#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
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
    Cow ray tracer
    MP2 Google doc link: https://docs.google.com/document/d/1INN31AYnI4K1SPYwHzv-urN0GGfs8DJrewOSgw2h97k/edit?usp=sharing
**/
int main(){
    //Regular grid toggle
    int acc = 1;

    //Camera
    float* cam = new float[3];
    cam[0] = 0;
    cam[1] = 0;
    cam[2] = 1000;

    //plane constructor
    float* point = new float[3];
    point[0] = 0;
    point[1] = 249;
    point[2] = 0;
    float* normy = new float[3];
    normy[0] = 0;
    normy[1] = 1;
    normy[2] = 0;
    int* planeMat = new int[3];
    planeMat[0] = 0;
    planeMat[1] = 0;
    planeMat[2] = 255;
    Plane plane(point,normy,planeMat);

    //light constructor
    float ldir[3] = {.4,.4,-1};
    float kd2 = .85;
    float illum2 = 1.0;
    DirectionalL light(ldir,kd2,illum2);

    //Obj parser
    std::string stringy;
    int numFaces = 5804;
    int numVerts = 2904;
    float vertices[numVerts][3];
    int faces[numFaces][3];
    std::ifstream cowFile;
    cowFile.open("cow.obj");
    int v = 0;
    int f = 0;
    if(cowFile.is_open()){
        while(!cowFile.eof()){
            getline(cowFile,stringy);
            char* str = new char[stringy.length() + 1];
            if(stringy[0] == 'v'){
                strcpy(str, stringy.c_str());
                char* vert = strtok(str, " ");
                vert = strtok(NULL, " ");
                vertices[v][0] = atof(vert);
                vert = strtok(NULL, " ");
                vertices[v][1] = atof(vert);
                vert = strtok(NULL, " ");
                vertices[v][2] = atof(vert);
                v++;
            }
            if(stringy[0] == 'f'){
                strcpy(str, stringy.c_str());
                char* face = strtok(str, " ");
                face = strtok(NULL, " ");
                faces[f][0] = atoi(face);
                face = strtok(NULL, " ");
                faces[f][1] = atoi(face);
                face = strtok(NULL, " ");
                faces[f][2] = atoi(face);
                f++;
            }
            delete [] str;
        }
    }
    cowFile.close();
    // Uses parsed obj data to create triangles
    Triangle* cow = new Triangle[numFaces];
    float * min = new float[3];
    min[0] = 10000;
    min[1] = 10000;
    min[2] = 10000;
    float * max = new float[3];
    max[0] = -10000;
    max[1] = -10000;
    max[2] = -10000;
    for(int i = 0; i < numFaces; i++){
        float* verts[3];
        verts[0] = new float[3];
        verts[1] = new float[3];
        verts[2] = new float[3];

        for(int x = 0; x < 3; x++){
            verts[x][0] = vertices[faces[i][x]][0]*200;
            verts[x][1] = vertices[faces[i][x]][1]*-200+150;
            verts[x][2] = vertices[faces[i][x]][2]*200;
            
            for(int y = 0; y < 3; y++){
                if(verts[x][y] < min[y])
                    min[y] = verts[x][y];
                if(verts[x][y] > max[y])
                    max[y] = verts[x][y];
            }
        }
        int* cowMat = new int[3];
        cowMat[0] = 130;
        cowMat[1] = 120;
        cowMat[2] = 0;
        cow[i].setTri(verts[0], verts[1], verts[2], cowMat);
    }
    std::cout << printPoint(min) << std::endl;
    std::cout << printPoint(max) << std::endl;
    int widest = max[0] - min[0];
    int ywide = max[1] - min[1];
    if(ywide > widest)
        widest = ywide;
    int zwide = max[2] - min[2];
    if(zwide > widest)
        widest = zwide;
    int cellWidth = widest/8;
    //Make a regular grid using widest side of the mesh to make sure it is a cube
    Grid * cowBox = new Grid(min[0], min[1], min[2], widest, cellWidth);

    //Fill grid similarly to spheres
    int curInd = 0;
    //Grid is an array of vectors that have indices pushed into them
    std::vector<int>* gridCells = cowBox->getGridCells();
    int * counts = cowBox->getCounts();
    std::cout << "Starting to fill grid" << std::endl;
    int imin = cowBox->getMinX();
    int imax = cowBox->getMaxX();
    int jmin = cowBox->getMinY();
    int jmax = cowBox->getMaxY();
    int kmin = cowBox->getMinZ();
    int kmax = cowBox->getMaxZ();
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
                for(int x = 0; x < numFaces; x++){
                    if(curCell.overlap(cow[x].getBox())){
                        gridCells[curInd].push_back(x);
                        counts[curInd]++;
                    }
                }
                curInd++;
            }
        }
    }
    std::cout << "Finished filling grid" << std::endl;
    //background color
    int background[3] = {0,0,0};
    //image creation
    CImg<float> img(512,512,1,3);
    int shapes = numFaces+1;
    float* t = new float [shapes];
    int* drawColor = new int[3];
    float* hitPoint = new float[3];
    int cowHit = 0;
    int planeHit = 0;
    int miss = 0;
    for(int i = 0; i < img.height(); i++)
        for(int j = 0; j < img.width(); j++){
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

            //if regular grid is toggled
            if(acc == 1){
                int ct = -1;
                int drawX = -1;
                int drawT = -1;
                int drawPlane = 0;
                //traverse the grid starting with the first cell the ray hits
                int startCell = cowBox->getFirstCell(ray);
                int curCell = startCell;
                while(ct == -1 && curCell > 0){
                    ct = -1;
                    int count = counts[curCell];
                    float* acct = new float[count];
                    //see if it hits any of the cow triangles
                    for(int x = 0; x < count; x++){
                        acct[x] = cow[gridCells[curCell][x]].intersectRay(ray);
                    }
                    //if any are hit, ct will be set to their index
                    if(count > 0)
                        ct = closest(acct,count);
                    //if none are hit, go to the next cell
                    if(ct == -1){
                        curCell = cowBox->getNextCell(ray,curCell);
                    }
                    //if one is hit, save the index into drawX
                    else{
                        drawX = gridCells[curCell][ct];
                    }
                    delete [] acct;
                }
                //if it never hit the cow, try to see if it hit the plane still
                if(startCell == -1 || ct == -1){
                    drawT = plane.intersectRay(ray);
                    //std::cout << pt << std::endl;
                    if(drawT > 0)
                        drawPlane = 1;
                }
                //if you hit the plane, draw it
                if(drawPlane){
                    planeHit++;
                    ray->getPoint(drawT,hitPoint);
                    light.phong(plane.getNormal(),plane.getMaterial(),drawColor);
                    float * shadowDir = new float[3];
                    mult(light.getDirection(),-1,shadowDir);
                    Ray* shadowRay = new Ray(hitPoint, shadowDir);
                    if(cowBox->getBox()->intersectRay(shadowRay) > 0){
                        for(int x = 0; x < numFaces; x++){
                            t[x] = cow[x].intersectRay(shadowRay);
                        }
                        float st = closest(t,numFaces);
                        if(st > 0)
                            img.draw_point(i, j, background);
                        else
                            img.draw_point(i, j, drawColor);
                    }
                    else
                        img.draw_point(i, j, drawColor);
                }
                //if you hit the cow, draw it
                else if(ct != -1){
                    cowHit++;
                    float* cowNorm = cow[drawX].getNormal();
                    light.phong(cowNorm,cow[drawX].getMaterial(),drawColor);
                    img.draw_point(i, j, drawColor);
                }
                //if no shapes are hit draw the background
                else{
                    miss++;
                    img.draw_point(i, j, background);
                }
            }
            //non accelerated
            else{
                int ct = -1;
                //check every shape
                for(int x = 0; x < shapes; x++){
                    if(x == 0)
                        t[x] = plane.intersectRay(ray);
                    else
                        t[x] = cow[x-1].intersectRay(ray);
                }
                //set ct to the index of the closest
                ct = closest(t,shapes);
                //draw the cow triangle if it is hit first
                if(ct != -1 && ct != 0){
                    cowHit++;
                    light.phong(cow[ct-1].getNormal(),cow[ct-1].getMaterial(),drawColor);
                    img.draw_point(i, j, drawColor);
                }
                //draw the plane if it is hit first
                else if(ct == 0){
                    planeHit++;
                    ray->getPoint(t[0],hitPoint);
                    light.phong(plane.getNormal(),plane.getMaterial(),drawColor);
                    //shadow calculation
                    float * shadowDir = new float[3];
                    mult(light.getDirection(),-1,shadowDir);
                    Ray* shadowRay = new Ray(hitPoint, shadowDir);
                    if(cowBox->getBox()->intersectRay(shadowRay) > 0){
                        for(int x = 0; x < shapes-1; x++){
                            t[x] = cow[x].intersectRay(shadowRay);
                        }
                        float st = closest(t,shapes);
                        if(st > 0)
                            img.draw_point(i, j, background);
                        else
                            img.draw_point(i, j, drawColor);
                    }
                    else
                        img.draw_point(i, j, drawColor);
                }
                //if no shapes are hit draw the background
                else{
                    miss++;
                    img.draw_point(i, j, background);
                }
            }
            delete ray;
        }
    delete [] t;
    delete [] drawColor;
    delete [] hitPoint;
    delete [] cow;
    delete [] cam;
    std::cout << "Cow Hits: " << cowHit << std::endl;
    std::cout << "Plane Hits: " << planeHit << std::endl;
    std::cout << "Misses: " << miss << std::endl;
    img.save_png("test.png");
    return 0;
}