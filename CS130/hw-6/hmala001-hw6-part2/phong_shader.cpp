#include "light.h"
#include "parse.h"
#include "object.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

Phong_Shader::Phong_Shader(const Parse* parse,std::istream& in)
{
    in>>name;
    color_ambient=parse->Get_Color(in);
    color_diffuse=parse->Get_Color(in);
    color_specular=parse->Get_Color(in);
    in>>specular_power;
}

vec3 Phong_Shader::
Shade_Surface(const Render_World& render_world,const Ray& ray,const Hit& hit,
    const vec3& intersection_point,const vec3& normal,int recursion_depth) const
{
    Debug_Scope bruh;

    vec3 world_ambient_default = (render_world.ambient_color != nullptr ? render_world.ambient_color->Get_Color(hit.uv) : vec3());
    //Pixel_Print("World Ambient: ", world_ambient_default[0], " ", world_ambient_default[1], " ", world_ambient_default[2]);

    vec3 ambient_math_thing = (color_ambient != nullptr ? color_ambient->Get_Color(hit.uv) : vec3());
    ambient_math_thing *= world_ambient_default;

    vec3 ambient_component = ambient_math_thing * render_world.ambient_intensity;

    Pixel_Print("ambient: (", ambient_component[0]," ", ambient_component[1]," ", ambient_component[2],")");

    vec3 diffuse_component;
    vec3 specular_component; //Do this with every single light source

    vec3 ray_hit_pos = (hit.dist * ray.direction) + ray.endpoint;
    for (size_t i = 0; i < render_world.lights.size(); i++){
        const Light *current = render_world.lights[i];

        vec3 light_ray = (current->position - ray_hit_pos);
        Ray shadow(ray_hit_pos, light_ray);
        
        double shadow_distance = render_world.Closest_Intersection(shadow).second.dist;
        bool can_get_color = (shadow_distance > light_ray.magnitude()) || shadow_distance < small_t;
        //Pixel_Print(shadow_distance," > ", light_ray.magnitude(), " = ", can_get_color);

        if ((render_world.enable_shadows && can_get_color) || !render_world.enable_shadows){
            double norm_dot_light = dot(normal.normalized(), light_ray.normalized()); //If it errors here, I know why

            //---------------Diffuse Section
            vec3 local_diffuse = current->Emitted_Light(light_ray) * color_diffuse->Get_Color(hit.uv);
            local_diffuse *= std::max(norm_dot_light, 0.0);

            //---------------Specular Section
            vec3 local_specular = current->Emitted_Light(light_ray) * color_specular->Get_Color(hit.uv);
            vec3 reflected_ray = ((2 * (norm_dot_light) * normal.normalized()) - light_ray.normalized());
            local_specular *= std::pow(std::max(dot(reflected_ray.normalized(), (ray.direction * -1).normalized()), 0.0), specular_power);
            //Pixel_Print("reflected: ", reflected_ray[0], " ", reflected_ray[1], " ", reflected_ray[2]);

            diffuse_component += local_diffuse;
            specular_component += local_specular;

            Pixel_Print("shading for light ", current->name,": diffuse: (", local_diffuse[0]," ", local_diffuse[1]," ", local_diffuse[2],"); specular: (", local_specular[0]," ", local_specular[1]," ", local_specular[2],")");
        }
    }

    vec3 color = (ambient_component + diffuse_component + specular_component);
    Pixel_Print("final color ", color);
    return color;
}
