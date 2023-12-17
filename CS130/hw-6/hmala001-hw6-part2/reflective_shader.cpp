#include "reflective_shader.h"
#include "parse.h"
#include "ray.h"
#include "render_world.h"

Reflective_Shader::Reflective_Shader(const Parse* parse,std::istream& in)
{
    in>>name;
    shader=parse->Get_Shader(in);
    in>>reflectivity;
    reflectivity=std::max(0.0,std::min(1.0,reflectivity));
}

vec3 Reflective_Shader::
Shade_Surface(const Render_World& render_world,const Ray& ray,const Hit& hit,
    const vec3& intersection_point, const vec3& normal,int recursion_depth) const
{       
    Debug_Scope ds;
    
    vec3 local_color = shader->Shade_Surface(render_world, ray, hit, intersection_point, normal, recursion_depth);
    
    double norm_dot_ray = dot(normal, ray.direction);
    vec3 reflection = -1.0 * ((2 * (norm_dot_ray) * normal.normalized()) - ray.direction);
    vec3 reflection_color = render_world.Cast_Ray(Ray(intersection_point, reflection), recursion_depth);

    vec3 fin = ((1 - reflectivity) * local_color) + ((reflectivity) * reflection_color);

    Pixel_Print("reflected ray: (end: ",intersection_point,"; dir: ", reflection,"); reflected color: ", reflection_color,"; object color: ", local_color,"; final color: ", fin);
    return fin;
}
