// Student Name: Henri Malahieude
// Student ID: 862268736
#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool enable_acceleration;

Render_World::~Render_World()
{
    for(auto a:all_objects) delete a; //ok, but you know how long this will last.
    for(auto a:all_shaders) delete a; //Why are we using time to delete this when the OS will reclaim all memory anyways?
    for(auto a:all_colors) delete a;  //The OS is the greatest garbage collector
    for(auto a:lights) delete a;
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
std::pair<Shaded_Object,Hit> Render_World::Closest_Intersection(const Ray& ray) const
{
    Shaded_Object obj;
    Hit h;
    for (unsigned i = 0; i < objects.size(); i++){
        Hit test = objects.at(i).object->Intersection(ray, 0);
        if (test.dist >= small_t && (h.dist < 0 || test.dist < h.dist)){
            obj = objects.at(i);
            h = test;
        }
    }

    return {obj, h};
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    vec3 eye = camera.position;
    vec3 pixel_pos = camera.World_Position(pixel_index);

    Ray ray(eye, pixel_pos - eye);
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth) const
{
    vec3 color;
    
    std::pair<Shaded_Object, Hit> cast = Closest_Intersection(ray);

    if (cast.second.dist >= small_t){
        color = cast.first.shader->Shade_Surface(*this, ray, cast.second, vec3(0, 0, 0), cast.first.object->Normal(ray, cast.second), recursion_depth);
    }else{
        color = background_shader != nullptr ? 
            background_shader->Shade_Surface(*this, ray, cast.second, vec3(0, 0, 0), cast.first.object->Normal(ray, cast.second), recursion_depth) : 
            vec3(0, 0, 0);
    }

    return color;
}
