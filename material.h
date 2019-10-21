#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "hitable_list.h"

class material{
    public:
        virtual bool scatter(const ray& r_in, const hit_record hit, vec3& attenuation, ray& scattered) const = 0;
};

#endif