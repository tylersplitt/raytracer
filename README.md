# raytracer
Ray tracer for CS 419

Code written using VSCode and in C++

Image processing library CImg used

In Makefile, use raytracer3.cpp for reflected spheres lit by area light and raytracer4.cpp for cow instancing attempt

Folder mp1pics contains the 5 pictures that were on the assignment mp1.

Folder mp2pics contains the 2 pictures that were on the assignment mp2.
	cow.png contains a rendering of a cow on a plane lit using 
		a directional light with shadows.
	spheres.png contains a rendering of many spheres in front of the camera 
		using a point light with specular and diffuse reflections as well as shadows.

Folder mp3pics contains 3 pictures
	mp3-1.png contains one perspective of a scene containing two spheres lit 
		by an area light and reflected in a mirror
	mp3-2.png is another perspective of the same scene
	mp3-3.png is an image of a cow lit by an area light and reflected in a mirror
			The image is very buggy. 
			The cow is an instance but I only managed to get one instance to appear
			before I ran out of time.

The cow image used 64 rays per shadow and used a total of 16411308 rays
	 and ran in about 6 minutes

The spheres image used 256 rays per shadow and used a total of 64635588 rays 
	and ran in about 1 minute

Code runs on Ubuntu 14.4 but I havent tried it elsewhere

Code can also be found at www.github.com/tylersplitt/raytracer