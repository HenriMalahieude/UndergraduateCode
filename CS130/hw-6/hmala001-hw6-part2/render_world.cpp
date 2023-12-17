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
    Debug_Scope dd;

    Shaded_Object obj;
    Hit h;
    for (unsigned i = 0; i < objects.size(); i++){
        Hit test = objects.at(i).object->Intersection(ray, 0);
        if (test.dist >= small_t){
            Pixel_Print("intersect test with ", objects[i].object->name, "; hit: (dist: ", test.dist,"; triangle: ", test.triangle, "; uv: (", test.uv[0], " ", test.uv[1],"))");
            if ((h.dist < 0 || test.dist < h.dist)){
                obj = objects.at(i);
                h = test;
            }
        }else{
            Pixel_Print("no intersection with ", objects[i].object->name);
        }
    }

    Pixel_Print("closest intersection; obj: ", (obj.object != nullptr ? obj.object->name : "nil"), "; hit: (dist: ", h.dist,"; triangle: ", h.triangle, "; uv: (", h.uv[0], " ", h.uv[1],"))");
    return {obj, h};
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    Debug_Scope dd;
    Pixel_Print("debug pixel: -x ", pixel_index[0], " -y ", pixel_index[1]);

    vec3 eye = camera.position;
    vec3 pixel_pos = camera.World_Position(pixel_index);

    Ray ray(eye, pixel_pos - eye);
    vec3 color = Cast_Ray(ray, recursion_depth_limit);
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
vec3 Render_World::Cast_Ray(const Ray& ray, int recursion_depth) const
{
    Debug_Scope dd;
    Pixel_Print("cast ray: (end: (", ray.endpoint[0], " ", ray.endpoint[1], " ", ray.endpoint[2], "); dir: (", ray.direction[0], " ", ray.direction[1], " ", ray.direction[2], "))");

    vec3 color;

    if (recursion_depth <= 0){
        Pixel_Print("ray too deep; return black");
        return vec3();
    }

    std::pair<Shaded_Object, Hit> cast = Closest_Intersection(ray);

    if (cast.second.dist >= small_t){
        vec3 location = ray.endpoint + (cast.second.dist * ray.direction);
        vec3 normal = cast.first.object->Normal(ray, cast.second);
        
        Pixel_Print("call Shade_Surface with location (", location[0], " ", location[1], " ", location[2], "); normal: (", normal[0], " ", normal[1], " ", normal[2], ")");
        
        color = cast.first.shader->Shade_Surface(*this, ray, cast.second, location, normal, recursion_depth-1);
    }else{
        Pixel_Print("use background_shader");
        if (background_shader != nullptr){
            if (cast.first.object != nullptr){
                color = background_shader->Shade_Surface(*this, ray, cast.second, vec3(0, 0, 0), cast.first.object->Normal(ray, cast.second), recursion_depth-1);
            }else{
                color = background_shader->Shade_Surface(*this, ray, cast.second, vec3(0, 0, 0), vec3(0, 1, 0), recursion_depth-1);
            }
        }else{
            color = vec3(0, 0, 0);
        }
    }

    return color;
}
