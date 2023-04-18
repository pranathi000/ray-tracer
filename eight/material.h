#ifndef MATERIALH
#define MATERIALH

struct hit_record;

class material {
public:
 virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
 lambertian(const vec3& a) : albedo(a) {}
 virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
  vec3 target = rec.p + rec.normal + random_in_unit_sphere();
  scattered = ray(rec.p, target-rec.p);
  attenuation = albedo;
  return true;
 }
 vec3 albedo;
};

class metal : public material {
public:
 metal(const vec3& a, float f) : albedo(a) {if(f<1) fuzz=f; else fuzz=1;}
 virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
  vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
  scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
  attenuation = albedo;
  return (dot(scattered.direction(),rec.normal)>0);
 }
 vec3 albedo;
 int fuzz;
};


class dielectric : public material {
public:
 dielectric(float ri) : ref_index(ri) 
 {
 
 }
 
 virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
	vec3 outward_normal;
	vec3 reflected = reflect(r_in.direction(), rec.normal);
	float ni_over_nt;
	attenuation = vec3(1.0,1.0,0.0);
	vec3 refracted;
	if(dot(r_in.direction(), rec.normal) > 0){
		 outward_normal = -rec.normal;
		 ni_over_nt = ref_index;
		 	
	}
	else{
		outward_normal = rec.normal;
		ni_over_nt = 1.0 / ref_index;
		 	
	}
	if(refract(r_in.direction(), outward_normal,ni_over_nt, refracted)){
		scattered = ray(rec.p, refracted);
		
	}
	else{
		scattered = ray(rec.p, reflected);
	}
	return true;
	
 }
 float ref_index;
 //which is refracted index
 


};


#endif
