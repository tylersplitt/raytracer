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
#include "Util/ray.h"
#include "Lights/directional_l.h"
#include "Lights/point_l.h"
#include "Util/func.h"
#include "Util/point3D.h"

using namespace std;

/**
    Cow ray tracer
    MP2 Google doc link: https://docs.google.com/document/d/1INN31AYnI4K1SPYwHzv-urN0GGfs8DJrewOSgw2h97k/edit?usp=sharing
**/
int main(){
    //Regular grid toggle
    // int acc = 1;

    //Camera
    Point3D<float> cam(0,0,1000);

    //plane constructor
    Point3D<float>* point = new Point3D<float>(0,249,0);
    Point3D<float>* normy = new Point3D<float>(0,1,0);
    Point3D<int>* planeMat = new Point3D<int>(0,0,255);
    Plane plane(point,normy,planeMat);

    //light constructor
    Point3D<float> lpos(0,-200,600);
    float kd2 = .85;
    float illum2 = 2.0;
    PointL light(lpos,kd2,illum2);

    //Obj parser
    std::string stringy;
    int numFaces = 5804;
    int numVerts = 2904;
    float vertices[numVerts][3];
    int faces[numFaces][3];
    std::ifstream cowFile;
    cowFile.open("Obj/cow.obj");
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
                faces[f][0] = atoi(face)-1;
                face = strtok(NULL, " ");
                faces[f][1] = atoi(face)-1;
                face = strtok(NULL, " ");
                faces[f][2] = atoi(face)-1;
                f++;
            }
            delete [] str;
        }
    }
    cowFile.close();

    // Uses parsed obj data to create triangles
    Triangle* cow = new Triangle[numFaces];
    Point3D<float>* min = new Point3D<float>(10000,10000,10000);
    Point3D<float>* max = new Point3D<float>(-10000,-10000,-10000);
    for(int i = 0; i < numFaces; i++){
        Point3D<float>* verts[3];
        verts[0] = new Point3D<float>();
        verts[1] = new Point3D<float>();
        verts[2] = new Point3D<float>();

        for(int x = 0; x < 3; x++){
            verts[x]->setX(vertices[faces[i][x]][0]*200);
            verts[x]->setY(vertices[faces[i][x]][1]*-200+160);
            verts[x]->setZ(vertices[faces[i][x]][2]*200-100);

            if(verts[x]->getX() < min->getX())
                min->setX(verts[x]->getX());
            if(verts[x]->getX() > max->getX())
                max->setX(verts[x]->getX());
            if(verts[x]->getY() < min->getY())
                min->setY(verts[x]->getY());
            if(verts[x]->getY() > max->getY())
                max->setY(verts[x]->getY());
            if(verts[x]->getZ() < min->getZ())
                min->setZ(verts[x]->getZ());
            if(verts[x]->getZ() > max->getZ())
                max->setZ(verts[x]->getZ());
        }
        Point3D<int>* cowMat = new Point3D<int>(130,120,0);
        cow[i].setTri(verts[0], verts[1], verts[2], cowMat);
    }
    int widest = max->getX() - min->getX();
    int ywide = max->getY() - min->getY();
    if(ywide > widest)
        widest = ywide;
    int zwide = max->getZ() - min->getZ();
    if(zwide > widest)
        widest = zwide;
    int cellWidth = widest/8;
    //Make a regular grid using widest side of the mesh to make sure it is a cube
    Grid * cowBox = new Grid(min->getX(), min->getY(), min->getZ(), widest, cellWidth);
    cout << widest << endl;
    //Fill grid similarly to spheres
    int curInd = 0;
    //Grid is an array of vectors that have indices pushed into them
    vector<int>* gridCells = cowBox->getGridCells();
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
                Point3D<float>* minC = new Point3D<float>(i,j,k);
                Point3D<float>* maxC = new Point3D<float>(i+cellWidth,j+cellWidth,k+cellWidth);
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
    // for(int i = 0; i < cowBox->getTotCells(); i++){
    //     cout << i << " - " << counts[i] << endl;
        // cout << counts[i] << endl;
        // for(int j = 0; j < counts[i]; j++){
        //     cow[gridCells[i][j]].printTriangle();
        // }
    // }


    std::cout << "Finished filling grid" << std::endl;
    //background color
    int background[3] = {0,0,0};
    //image creation
    cimg_library::CImg<float> img(512,512,1,3);
    int cowHit = 0;
    int planeHit = 0;
    int miss = 0;
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

            //if regular grid is toggled
            int ct = -1;
            int drawX = -1;
            float drawT = -1;
            int drawPlane = 0;
            //traverse the grid starting with the first cell the ray hits
            int startCell = cowBox->getFirstCell(ray);
            int curCell = startCell;
            while(ct == -1 && curCell > 0){
                ct = -1;
                int count = counts[curCell];
                float* t = new float[count];
                //see if it hits any of the cow triangles
                for(int x = 0; x < count; x++){
                    t[x] = cow[gridCells[curCell][x]].intersectRay(ray);
                }
                //if any are hit, ct will be set to their index
                if(count > 0)
                    ct = closest(t,count);
                //if none are hit, go to the next cell
                if(ct == -1){
                    curCell = cowBox->getNextCell(ray,curCell);
                }
                //if one is hit, save the index into drawX
                else{
                    drawX = gridCells[curCell][ct];
                    drawT = t[ct];
                }
                delete [] t;
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
                hitPoint = ray->getPoint(drawT);
                // cout << drawT << endl;
                drawColor = light.phong(hitPoint,*(plane.getNormal()),*(plane.getMaterial()),ray);
                Point3D<float> shadowDir = light.getDirectionTo(hitPoint)*-1;
                Ray* shadowRay = new Ray(hitPoint, shadowDir);
                int st = -1;
                //traverse the grid starting with the first cell the ray hits
                int startCell = cowBox->getFirstCell(shadowRay);
                int curCell = startCell;
                while(st == -1 && curCell > 0){
                    st = -1;
                    int count = counts[curCell];
                    float* t = new float[count];
                    for(int x = 0; x < count; x++){
                        t[x] = cow[gridCells[curCell][x]].intersectRay(shadowRay);
                    }
                    if(count > 0)
                        st = closest(t,count);
                    if(st == -1){
                        curCell = cowBox->getNextCell(shadowRay,curCell);
                    }
                    delete [] t;
                }
                if(st > 0)
                    img.draw_point(i, j, background);
                else{
                    int col[3] = {drawColor.getX(),drawColor.getY(),drawColor.getZ()};
                    img.draw_point(i, j, col);
                }
            }
            //if you hit the cow, draw it
            else if(ct != -1){
                cowHit++;
                hitPoint = ray->getPoint(drawT);
                // cout << "Cow" << endl;
                Point3D<float> cNorm = cow[drawX].getNormal();
                Point3D<int>* cMat = cow[drawX].getMaterial();
                drawColor = light.phong(hitPoint,cNorm,*cMat,ray);
                int col[3] = {drawColor.getX(),drawColor.getY(),drawColor.getZ()};
                img.draw_point(i, j, col);
            }
            //if no shapes are hit draw the background
            else{
                miss++;
                img.draw_point(i, j, background);
            }
            delete ray;
        }
    delete [] cow;
    std::cout << "Cow Hits: " << cowHit << std::endl;
    std::cout << "Plane Hits: " << planeHit << std::endl;
    std::cout << "Misses: " << miss << std::endl;
    img.save_png("Pics/test.png");
    return 0;
}