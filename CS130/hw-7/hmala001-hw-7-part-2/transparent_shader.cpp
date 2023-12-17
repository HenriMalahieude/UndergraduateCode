#include "transparent_shader.h"
#include "parse.h"
#include "ray.h"
#include "render_world.h"

Transparent_Shader::
Transparent_Shader(const Parse* parse,std::istream& in)
{
    in>>name>>index_of_refraction>>opacity;
    shader=parse->Get_Shader(in);
    assert(index_of_refraction>=1.0);
}

// Use opacity to determine the contribution of this->shader and the Schlick
// approximation to compute the reflectivity.  This routine shades transparent
// objects such as glass.  Note that the incoming and outgoing indices of
// refraction depend on whether the ray is entering the object or leaving it.
// You may assume that the object is surrounded by air with index of refraction
// 1.
vec3 Transparent_Shader::
Shade_Surface(const Render_World& render_world,const Ray& ray,const Hit& hit,
    const vec3& intersection_point,const vec3& normal,int recursion_depth) const
{
    Debug_Scope ds;

    //Reflected Color
    double norm_dot_ray = dot(normal.normalized(), ray.direction);
    Ray reflected_ray = Ray(intersection_point, -1.0 * (2*norm_dot_ray*normal - ray.direction));
    vec3 C_r = render_world.Cast_Ray(reflected_ray, recursion_depth);

    Pixel_Print("reflected ray: ", reflected_ray, "; reflected color: ", C_r);

    //Transmitted Color
    
    bool is_entering = dot(normal.normalized(), ray.direction) < 0;
    double n1 = (is_entering) ? 1 : index_of_refraction;
    double n2 = (is_entering) ? index_of_refraction : 1;

    vec3 v = -1.0 * ray.direction;
    vec3 n = (is_entering) ? normal.normalized() : (-1.0 * normal.normalized());
    double cosTheta1 = dot(n, v);
    
    //Class Equation
    double sinTheta1 = std::sqrt(1 - std::pow(cosTheta1, 2.0));
    double sinTheta2 = (n1/n2) * sinTheta1;
    double cosTheta2 = std::sqrt(1 - std::pow(sinTheta2, 2.0));
    vec3 t = ((-1.0 * cosTheta2) * n) + ((-1.0 * (n1/n2)) * (v - cosTheta1 * n));
    Ray transmit = Ray(intersection_point, t);
    vec3 C_tr = render_world.Cast_Ray(transmit, recursion_depth);

    double R0 = std::pow(((n1 - n2) / (n1 + n2)), 2.0);
    double R = (R0) + ((1 - R0) * std::pow((1 - cosTheta1), 5.0));
    if (sinTheta2 > 1){
        R = 1;
    }

    vec3 combinedColor = (R * C_r) + ((1 - R) * C_tr);

    Pixel_Print("transmitted ray: ", transmit, "; transmitted color: ", C_tr, "; Schlick reflectivity: ", R, "; combined color: ", combinedColor);

    //Object Color
    vec3 C_o = shader->Shade_Surface(render_world, ray, hit, intersection_point, normal, recursion_depth);

    //Final Color
    vec3 fin = ((opacity) * C_o) + (1 - opacity) * combinedColor;

    Pixel_Print("object color: ", C_o, "; final color: ", fin);
    //Color = (1 - opacity) * C0 + (opacity) * R * Cr + (opacity) * (1-R) * Ct
    return fin;
}
