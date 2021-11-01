#pragma once
#include "Ray.h"
#include "Material.h"
//#include <ostream>

class Geometry
{
public:
    Geometry() = default;
    virtual ~Geometry() = default;

    virtual bool Hit(const ray_t& r, float tMin, float tMax, raycastHit_t& hit) = 0;
    Geometry(std::shared_ptr<Material>  material) : material{ material } {}

public: 
    std::shared_ptr<Material>  material;
};