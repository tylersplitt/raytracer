all: raytracer exec clean

raytracer: raytracer.o sphere.o plane.o ray.o light.o func.o
	g++ -o raytracer raytracer.o sphere.o plane.o ray.o light.o func.o -lpthread -lX11

raytracer.o: raytracer.cpp
	g++ -c raytracer.cpp -lpthread -lX11

sphere.o: sphere.cpp sphere.h
	g++ -c sphere.cpp

plane.o: plane.cpp plane.h
	g++ -c plane.cpp

ray.o: ray.cpp ray.h
	g++ -c ray.cpp

light.o: light.cpp light.h
	g++ -c light.cpp

func.o: func.cpp func.h
	g++ -c func.cpp

exec: raytracer
	./raytracer

clean:
	rm -f raytracer raytracer.o sphere.o ray.o light.o func.o
