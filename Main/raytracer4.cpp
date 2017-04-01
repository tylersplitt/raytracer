#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "CImg.h"
#include "Shapes/sphere.h"
#include "Shapes/plane.h"
#include "Shapes/triangle.h"
#include "Shapes/rect.h"
#include "Shapes/BB.h"
#include "Shapes/grid.h"
#include "Util/ray.h"
#include "Lights/directional_l.h"
#include "Lights/point_l.h"
#include "Lights/area_l.h"
#include "Util/func.h"
#include "Util/point3D.h"

using namespace std;

/**
    Spheres ray tracer
    MP2 Google doc link: https://docs.google.com/document/d/1INN31AYnI4K1SPYwHzv-urN0GGfs8DJrewOSgw2h97k/edit?usp=sharing
**/
int main(){

    //Camera
    Point3D<float> cam(0,0,1000);

    int rayCount = 0;

	//rect constructors
	Point3D<float>* rpt4 = new Point3D<float>(-350,100,-200);
	Point3D<float>* rpt3 = new Point3D<float>(-350,200,-200);
	Point3D<float>* rpt2 = new Point3D<float>(-350,200,-100);
	Point3D<float>* rpt1 = new Point3D<float>(-350,100,-100);
	Point3D<int>* rMat = new Point3D<int>(255,255,255);
	Rect* rect = new Rect(rpt1,rpt2,rpt3,rpt4,rMat);

    //rect constructors
	Point3D<float>* mpt1 = new Point3D<float>(50,240,-600);
	Point3D<float>* mpt2 = new Point3D<float>(50,0,-550);
	Point3D<float>* mpt3 = new Point3D<float>(250,0,-300);
	Point3D<float>* mpt4 = new Point3D<float>(250,240,-350);
	Point3D<int>* mMat = new Point3D<int>(255,255,255);
	Rect* mirror = new Rect(mpt1,mpt2,mpt3,mpt4,mMat);

    cout << mirror->getNormal() << endl;

    //light constructor;
    float kd = .75;
    float illum = 1.4;
    AreaL light(rect,kd,illum);
    // cout << light.getPosition() << endl;

    //plane constructors
    const int numPlanes = 4;
    Plane * planes = new Plane[numPlanes];
    Point3D<float>* point0 = new Point3D<float>(0,256,0);
    Point3D<float>* normy0 = new Point3D<float>(0,1,0);
    Point3D<int>* planeMat0 = new Point3D<int>(0,0,255);
    planes[0].setPlane(point0,normy0,planeMat0);
    Point3D<float>* point1 = new Point3D<float>(0,0,-700);
    Point3D<float>* normy1 = new Point3D<float>(0,0,-1);
    Point3D<int>* planeMat1 = new Point3D<int>(255,190,255);
    planes[1].setPlane(point1,normy1,planeMat1);
    Point3D<float>* point2 = new Point3D<float>(256,0,0);
    Point3D<float>* normy2 = new Point3D<float>(1,0,0);
    Point3D<int>* planeMat2 = new Point3D<int>(255,0,0);
    planes[2].setPlane(point2,normy2,planeMat2);
    Point3D<float>* point3 = new Point3D<float>(-400,0,0);
    Point3D<float>* normy3 = new Point3D<float>(-1,0,0);
    Point3D<int>* planeMat3 = new Point3D<int>(0,255,0);
    planes[3].setPlane(point3,normy3,planeMat3);

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
    cout << "Parsing cow file" << endl;
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
    cout << "Creating cow object" << endl;
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
            verts[x]->setY(vertices[faces[i][x]][1]*-200);
            verts[x]->setZ(vertices[faces[i][x]][2]*200);

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
    cout << "Making cow grid" << endl;
    Grid * cowBox = new Grid(min->getX(), min->getY(), min->getZ(), widest, cellWidth);
    cout << "Grid made" << endl;
    //Fill grid similarly to spheres
    int curInd = 0;
    //Grid is an array of vectors that have indices pushed into them
    vector<int>* gridCells = cowBox->getGridCells();
    int * counts = cowBox->getCounts();
    std::cout << "Starting to fill cow grid" << std::endl;
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

    //Cow instances
    Point3D<float> trans1(-130,200,-200);
    Point3D<float> tempMin = *(cowBox->getMin())+trans1;
    Point3D<float> tempMax = *(cowBox->getMax())+trans1;

    Point3D<float>* newMin = new Point3D<float>(tempMin);
    Point3D<float>* newMax = new Point3D<float>(tempMax);
    BB* bb1 = new BB(newMin, newMax);

    Point3D<int>* mat1 = new Point3D<int>(255,0,0);
    
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
            rayCount++;

            //drawing variables
            int ct = -1;
            int drawPlane = -1;
			int drawRect = 0;
            int drawMirr = 0;
            float drawT = -1;
            int drawCow = -1;
            //gets starting cell of grid
            // if(bb1->intersectRay(ray) != -1){
                ray->setOrigin(ray->getOrigin()-trans1);

                int curCell = cowBox->getFirstCell(ray);
                counts = cowBox->getCounts();
                gridCells = cowBox->getGridCells();
                while(ct == -1 && curCell > 0){
                    ct = -1;
                    //gets #spheres in that cell
                    int count = counts[curCell];
                    float* t = new float[count];
                    //checks if any of them intersect
                    for(int x = 0; x < count; x++){
                        t[x] = cow[gridCells[curCell][x]].intersectRay(ray);
                    }
                    //gets the closest if any are in the cell
                    if(count > 0)
                        ct = closest(t,count);
                    //if there is no hit, it traverses to the next cell
                    if(ct == -1)
                        curCell = cowBox->getNextCell(ray,curCell);
                    else{
                        //sets the draw t value and index of the sphere that was hit
                        drawT = t[ct];
                        drawCow = gridCells[curCell][ct];
                    }
                    delete [] t;
                }

                ray->setOrigin(rayOr);
            // }

			float rectT = rect->intersectRay(ray);
            // rect->printRect();
            if(rectT != -1 && (drawT == -1 || (drawT != -1 && rectT < drawT))){
				drawT = rectT;
				drawRect = 1;
			}
            float mirrT = mirror->intersectRay(ray);
            if(mirrT != -1 && (drawT == -1 || (drawT != -1 && mirrT < drawT))){
				drawT = mirrT;
				drawMirr = 1;
			}
            if(ct == -1 && !drawRect && !drawMirr){
                float* t = new float[numPlanes];
                for(int x = 0; x < numPlanes; x++){
                    t[x] = planes[x].intersectRay(ray);
                }
                drawPlane = closest(t,numPlanes);
                //std::cout << pt << std::endl;
                if(drawPlane != -1)
                    drawT = t[drawPlane];
                delete [] t;
            }
			if(drawRect && !drawMirr){
				hitPoint = ray->getPoint(drawT);
				drawColor = light.phong(hitPoint,rect->getNormal(),*(rect->getMaterial()),ray);
				int col[3] = {drawColor.getX(),drawColor.getY(),drawColor.getZ()};
                img.draw_point(i, j, col);
			}
            else if(drawMirr){
                hitPoint = ray->getPoint(drawT);
				drawColor = light.phong(hitPoint,mirror->getNormal(),*(mirror->getMaterial()),ray);
                Point3D<int> reflCol;
                Point3D<float> reflHit;
                int refl = 0;
                Ray* reflRay = new Ray(hitPoint, mirror->getNormal());
                rayCount++;
                reflRay->setOrigin(reflRay->getOrigin()-trans1);
                int st = -1;
                int startCell = cowBox->getFirstCell(reflRay);
                int curCell = startCell;
                while(st == -1 && curCell > 0){
                    st = -1;
                    int count = counts[curCell];
                    float* t = new float[count];
                    for(int x = 0; x < count; x++){
                        t[x] = cow[gridCells[curCell][x]].intersectRay(reflRay);
                    }
                    if(count > 0)
                        st = closest(t,count);
                    if(st == -1){
                        curCell = cowBox->getNextCell(reflRay,curCell);
                    }
                    else{
                        refl = 1;
                        reflHit = reflRay->getPoint(t[st]);
                        Point3D<float> cNorm = cow[st].getNormal();
                        Point3D<int>* cMat = mat1;
                        reflCol = light.phong(hitPoint,cNorm,*cMat,ray);
                    }
                    delete [] t;
                }
                reflRay->setOrigin(hitPoint);
                if(!refl){
                    float reflT = rect->intersectRay(reflRay);
                    if(reflT != -1){
                        refl = 1;
                        reflHit = reflRay->getPoint(reflT);
                        reflCol = light.phong(reflHit,rect->getNormal(),*(rect->getMaterial()),reflRay);
                    }
                }
                if(!refl){
                    float* t = new float[numPlanes];
                    for(int x = 0; x < numPlanes; x++){
                        t[x] = planes[x].intersectRay(reflRay);
                    }
                    int reflPlane = closest(t,numPlanes);
                    if(reflPlane != -1){
                        refl = 1;
                        reflHit = reflRay->getPoint(t[reflPlane]);
                        reflCol = light.phong(reflHit,*(planes[reflPlane].getNormal()),*(planes[reflPlane].getMaterial()),reflRay);
                        float hitCount = 0;
                        int hitRect = 0;
                        float shadCount = 64;
                        float shadSqrt = sqrt(shadCount);
                        for(int x = 0; x < shadSqrt; x++){
                            for(int y = 0; y < shadSqrt; y++){
                                float step = sqrt(rect->getArea())/16;
                                float lx = rect->getPoint1()->getX();
                                float ly = rect->getPoint1()->getY() + step*x;
                                float lz = rect->getPoint1()->getZ() - step*y;
                                Point3D<float> lightTarg(lx,ly,lz);
                                // cout << lightTarg << endl;
                                Point3D<float> shadowDir = lightTarg - hitPoint;// + lightTarg;
                                // cout << shadowDir << endl;
                                Ray* shadowRay = new Ray(hitPoint, shadowDir);
                                rayCount++;
                                float maxT = shadowRay->timeToPoint(lightTarg);
                                // cout << maxT << endl;
                                // shadowRay->printRay();
                                // shadowRay->setDirection(shadowRay->getDirection()-trans1);
                                shadowRay->setOrigin(shadowRay->getOrigin()-trans1);
                                // shadowRay->printRay();
                                int st = -1;
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
                                if(st > 0){
                                    hitCount++;
                                }
                                shadowRay->setOrigin(hitPoint);
                            }
                        }
                        Point3D<float> shadowDir = light.getDirectionTo(reflHit)*-1;
                        Ray* shadowRay = new Ray(reflHit, shadowDir);
                        rayCount++;
                        float maxT = shadowRay->timeToPoint(light.getPosition());
                        float rectT = rect->intersectRay(shadowRay);
                        if(rectT != -1 && rectT < maxT){
                            hitRect = 1;
                        }
                        if(hitRect)
                            reflCol = (*(planes[reflPlane].getMaterial()))*.1;
                        else{
                            float hitPerc = hitCount/shadCount;
                            Point3D<int> shadowCol = reflCol*hitPerc*.9;
                            reflCol = reflCol - shadowCol;
                        }
                    }
                    delete [] t;
                }
                if(refl){
                    drawColor = reflCol;
                }
                int col[3] = {drawColor.getX(),drawColor.getY(),drawColor.getZ()};
                img.draw_point(i, j, col);
            }
            else if(drawPlane != -1){
                hitPoint = ray->getPoint(drawT);
                drawColor = light.phong(hitPoint,*(planes[drawPlane].getNormal()),*(planes[drawPlane].getMaterial()),ray);
                float hitCount = 0;
                int hitRect = 0;
                float shadCount = 64;
                float shadSqrt = sqrt(shadCount);
                for(int x = 0; x < shadSqrt; x++){
                    for(int y = 0; y < shadSqrt; y++){
                        float step = sqrt(rect->getArea())/16;
                        float lx = rect->getPoint1()->getX();
                        float ly = rect->getPoint1()->getY() + step*x;
                        float lz = rect->getPoint1()->getZ() - step*y;
                        Point3D<float> lightTarg(lx,ly,lz);
                        // cout << lightTarg << endl;
                        Point3D<float> shadowDir = lightTarg - hitPoint;// + lightTarg;
                        // cout << shadowDir << endl;
                        Ray* shadowRay = new Ray(hitPoint, shadowDir);
                        rayCount++;
                        float maxT = shadowRay->timeToPoint(lightTarg);
                        // cout << maxT << endl;
                        // shadowRay->printRay();
                        // shadowRay->setDirection(shadowRay->getDirection()-trans1);
                        shadowRay->setOrigin(shadowRay->getOrigin()-trans1);
                        // shadowRay->printRay();
                        int st = -1;
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
                        if(st > 0){
                            hitCount++;
                        }
                        shadowRay->setOrigin(hitPoint);
                    }
                }
                Point3D<float> shadowDir = light.getDirectionTo(hitPoint)*-1;
                Ray* shadowRay = new Ray(hitPoint, shadowDir);
                rayCount++;
                float maxT = shadowRay->timeToPoint(light.getPosition());
                float rectT = rect->intersectRay(shadowRay);
                if(rectT != -1 && rectT < maxT){
                    hitRect = 1;
                }
                if(hitRect)
                    drawColor = (*(planes[drawPlane].getMaterial()))*.1;
                else{
                    float hitPerc = hitCount/shadCount;
                    Point3D<int> shadowCol = drawColor*hitPerc*.9;
                    drawColor = drawColor - shadowCol;
                }
                int col[3] = {drawColor.getX(),drawColor.getY(),drawColor.getZ()};
				img.draw_point(i, j, col);
            }
            //draws the cow
            else if(ct != -1){
                hitPoint = ray->getPoint(drawT);
                Point3D<float> cNorm = cow[drawCow].getNormal();
                Point3D<int>* cMat = mat1;
                drawColor = light.phong(hitPoint,cNorm,*cMat,ray);
                int col[3] = {drawColor.getX(),drawColor.getY(),drawColor.getZ()};
                img.draw_point(i, j, col);
            }
            //if no shapes are hit draw the background
            else{
                img.draw_point(i, j, background);
            }
            delete ray;
        }
    // delete [] planes;
    // delete [] spheres;
    // delete rect;
	cout << "Total Rays Used: " << rayCount <<  endl;
    img.save_png("Pics/test4.png");
    return 0;
}