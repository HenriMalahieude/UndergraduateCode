// Student Name: Henri Malahieude
// Student ID: 862268736
#include "sphere.h"
#include "ray.h"

Sphere::Sphere(const Parse* parse, std::istream& in)
{
    in>>name>>center>>radius;
}

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    Hit h;
    vec3 doub_u = ray.endpoint - center;

    double thing1 = (dot(doub_u, ray.direction));

    double thing2 = thing1*thing1 - (dot(doub_u, doub_u) - (radius*radius));

    if (thing2 >= 0){
        double sect_p = -1*thing1 + sqrt(thing2);
        double sect_n = -1*thing1 - sqrt(thing2);

        if (sect_p >= small_t || sect_n >= small_t){
            if (sect_n >= small_t && sect_n < sect_p){
                h.dist = sect_n;
            }else{
                h.dist = sect_p;
            }
        }
    }

    return h;
}

vec3 Sphere::Normal(const Ray& ray, const Hit& hit) const
{
    vec3 normal;
    
    vec3 intersect_point = ray.endpoint + ray.direction * hit.dist;
    normal = (intersect_point - radius).normalized();

    return normal;
}

std::pair<Box,bool> Sphere::Bounding_Box(int part) const
{
    return {{center-radius,center+radius},false};
}
