CXXFLAGS  = -Wall -I.
FLAGS = -lpthread -lX11 

all: raytracer exec clean

raytracer: raytracer2.o sphere.o plane.o triangle.o BB.o grid.o ray.o directional_l.o point_l.o func.o 
	g++ -o raytracer raytracer2.o sphere.o plane.o triangle.o BB.o grid.o ray.o directional_l.o point_l.o func.o $(FLAGS)

raytracer.o: Main/raytracer.cpp
	g++ -c $(CXXFLAGS) Main/raytracer.cpp $(FLAGS)

raytracer2.o: Main/raytracer2.cpp
	g++ -c $(CXXFLAGS) Main/raytracer2.cpp $(FLAGS)

sphere.o: Shapes/sphere.cpp Shapes/sphere.h
	g++ -c $(CXXFLAGS) Shapes/sphere.cpp

plane.o: Shapes/plane.cpp Shapes/plane.h
	g++ -c $(CXXFLAGS) Shapes/plane.cpp

triangle.o: Shapes/triangle.cpp Shapes/triangle.h
	g++ -c $(CXXFLAGS) Shapes/triangle.cpp

BB.o: Shapes/BB.cpp Shapes/BB.h
	g++ -c $(CXXFLAGS) Shapes/BB.cpp

grid.o: Shapes/grid.cpp Shapes/grid.h
	g++ -c $(CXXFLAGS) Shapes/grid.cpp

ray.o: Main/ray.cpp Main/ray.h
	g++ -c $(CXXFLAGS) Main/ray.cpp

directional_l.o: Lights/directional_l.cpp Lights/directional_l.h
	g++ -c $(CXXFLAGS) Lights/directional_l.cpp

point_l.o: Lights/point_l.cpp Lights/point_l.h
	g++ -c $(CXXFLAGS) Lights/point_l.cpp

func.o: Main/func.cpp Main/func.h
	g++ -c $(CXXFLAGS) Main/func.cpp

exec: raytracer
	./raytracer

clean:
	rm -f raytracer **/*.o *.o
