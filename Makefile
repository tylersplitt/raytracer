CXXFLAGS  = -Wall -I.
FLAGS = -lpthread -lX11 

all: raytracer exec clean

test: test.o point3D.o
	g++ -o test test.o point3D.o $(FLAGS)

test.o: Main/test.cpp
	g++ -c $(CXXFLAGS) Main/test.cpp $(FLAGS)

execTest: test
	./test

raytracer: raytracer4.o sphere.o plane.o triangle.o rect.o BB.o grid.o ray.o directional_l.o point_l.o area_l.o func.o point3D.o 
	g++ -o raytracer raytracer4.o sphere.o plane.o triangle.o rect.o BB.o grid.o ray.o directional_l.o point_l.o area_l.o func.o point3D.o $(FLAGS)

raytracer.o: Main/raytracer.cpp
	g++ -c $(CXXFLAGS) Main/raytracer.cpp $(FLAGS)

raytracer2.o: Main/raytracer2.cpp
	g++ -c $(CXXFLAGS) Main/raytracer2.cpp $(FLAGS)

raytracer3.o: Main/raytracer3.cpp
	g++ -c $(CXXFLAGS) Main/raytracer3.cpp $(FLAGS)

raytracer4.o: Main/raytracer4.cpp
	g++ -c $(CXXFLAGS) Main/raytracer4.cpp $(FLAGS)

point3D.o: Util/point3D.cpp Util/point3D.h
	g++ -c $(CXXFLAGS) Util/point3D.cpp 

sphere.o: Shapes/sphere.cpp Shapes/sphere.h
	g++ -c $(CXXFLAGS) Shapes/sphere.cpp

plane.o: Shapes/plane.cpp Shapes/plane.h
	g++ -c $(CXXFLAGS) Shapes/plane.cpp

triangle.o: Shapes/triangle.cpp Shapes/triangle.h
	g++ -c $(CXXFLAGS) Shapes/triangle.cpp

rect.o: Shapes/rect.cpp Shapes/rect.h
	g++ -c $(CXXFLAGS) Shapes/rect.cpp

BB.o: Shapes/BB.cpp Shapes/BB.h
	g++ -c $(CXXFLAGS) Shapes/BB.cpp

grid.o: Shapes/grid.cpp Shapes/grid.h
	g++ -c $(CXXFLAGS) Shapes/grid.cpp

ray.o: Util/ray.cpp Util/ray.h
	g++ -c $(CXXFLAGS) Util/ray.cpp

directional_l.o: Lights/directional_l.cpp Lights/directional_l.h
	g++ -c $(CXXFLAGS) Lights/directional_l.cpp

point_l.o: Lights/point_l.cpp Lights/point_l.h
	g++ -c $(CXXFLAGS) Lights/point_l.cpp

area_l.o: Lights/area_l.cpp Lights/area_l.h
	g++ -c $(CXXFLAGS) Lights/area_l.cpp

func.o: Util/func.cpp Util/func.h
	g++ -c $(CXXFLAGS) Util/func.cpp

exec: raytracer
	./raytracer

clean:
	rm -f raytracer test **/*.o *.o
