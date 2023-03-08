//we are going to use a structure variable so that it definately have a color after the completion.

#include "ray.h"
struct hit_record{
	float t;
	vec3 p;
	vec3 normal;
	//these variables of just for tracking that if the rays hit or not !
};
class hitable{
	public:
		virtual bool hit(const ray r,float t_min, float t_max, hit_record& rec) const = 0; 
};

