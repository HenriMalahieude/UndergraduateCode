#include "flat_shader.h"
#include "parse.h"
#include "color.h"

Flat_Shader::Flat_Shader(const Parse* parse,std::istream& in)
{
    in>>name;
    color=parse->Get_Color(in);
}

vec3 Flat_Shader::Shade_Surface(const Render_World& render_world,const Ray& ray,const Hit& hit, 
    const vec3& intersection_point,const vec3& normal,int recursion_depth) const 
{    
    Debug_Scope dd;

    vec3 cc = color->Get_Color(hit.uv);

    Pixel_Print("flat shader; color: (", cc[0], " ", cc[1], " ", cc[2], ")");

    return cc;
}
