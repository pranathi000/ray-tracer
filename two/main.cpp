#include <iostream>
#include "sdltemplate.h"
//#include "vec3.h"
#include "ray.h"

bool hit_sphere(const vec3 center, float radius, const ray& r) {
 	vec3 oc = r.origin()-center;
 	float a = dot(r.direction(),r.direction()); //x*x+y*y+z*z nothing but dot product
 	//(bx^2+by^2)t^2 +(2(axbx + ayby))t + (ax^2+by^2 - r^2) = 0
 	// dot prod          dot prod
 	//the above code changes the color of the sphere
	//a is the ray origin
	//b is the ray direction
	//t is the hit distance
	//r or g is the ray radius.
 	float b = 2.0 * dot(oc, r.direction());
 	float c = dot(oc,oc) - radius*radius;
 	float discriminant = b*b - 4*a*c;
 	//return (discriminant > 0);
 	return (discriminant>0);


}
vec3 sphere;
float sphere_radius;
vec3 color(const ray& r){
	if(hit_sphere(vec3(0,0,-1),0.5,r) ){return vec3(0,0.1,0.1);}
	
	vec3 unit_dir= unit_vector(r.direction());
	float t= 0.5*(unit_dir.y() + 1.0);
	return (1.0-t)*vec3(1,1,1)+t*vec3(0.1,0.5,0.5);
	return (1.0-t)*vec3(1,1,1)+t*vec3(0.2,0.5,0.5);
	//The above changes the background of the sphere.

}

int main() {
	sphere = vec3(0,0,-1);  // we can also take take the z coor as 1.
	sphere_radius = 0.5;   //simply 1 unit diameter waali sphere
	int width = 800;
	int height = 400;
	std::cout << "P3\n" << width << " " << height << "\n255\n";
	sdltemplate::sdl("Ray Tracer", width, height);
	sdltemplate::loop();
	vec3 lower_left_corner(-2.0,-1.0,-1.0);
	vec3 horizontal(4.0,0.0,0.0); //this means the horizontal height is 4
	vec3 vertical(0.0,2.0,0.0);   //this means the vertical height is 2
	vec3 origin(0.0,0.0,-2.0);
	for(int y=height-1; y>=00; y--) {
		for(int x=0; x<width; x++) {
			float u = float(x)/ float(width);
			float v = float(y)/ float(height);
			ray r(origin, lower_left_corner + u*horizontal + v*vertical);
			vec3 col = color(r);
			int ir = int(255.99*col[0]);  
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
			sdltemplate::setDrawColor(sdltemplate::createColor(ir,ig,ib,255));
			sdltemplate::drawPoint(x,height-y);
		}
	}
	while(sdltemplate::running) {
		sdltemplate::loop();
	}
}
