#include "Scene.h"

glm::vec3 Scene::Trace(const ray_t& ray, float tMin, float tMax, raycastHit_t& hit, int depth)
{
    if (depth <= 0) return glm::vec3{ 0,0,0 };

    float tClosest = tMax;
    bool rayHit = false;
    for (auto& object : objects)
    {
        if (object->Hit(ray, tMin, tClosest, hit))
        {
            rayHit = true;
            tClosest = hit.t;
        }
    }

    /*
    if (rayHit)
    {
        glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
        glm::vec3 direction = glm::normalize(target - hit.point);

        ray_t newRay{ hit.point, direction };
        return { Trace(newRay, tMin, tMax, hit) * 0.5f };
    }
    */

    if (rayHit)
    {
        ray_t scattered;
        glm::vec3 attenuation;
        glm::vec3 emissive = hit.material->Emitter(hit.uv, hit.point);

        if (!hit.material->Scatter(ray, hit, attenuation, scattered))
        {
            return emissive;
        }


        if (hit.material->Scatter(ray, hit, attenuation, scattered))
        {
            return emissive + attenuation * Trace(scattered, tMin, tMax, hit, depth - 1);
        }
        else
        {
            return { 0, 0, 0 };
        }
    }

    // sky
    glm::vec3 direction = glm::normalize(ray.direction);
    float t = (direction.y + 1) * 0.5f;
    return glm::lerp(glm::vec3(1, 1, 1), glm::vec3(0.5f, 0.7f, 1), t) * 0.15f;

}

void Scene::Add(std::unique_ptr<Geometry> geometry)
{
	objects.push_back(std::move(geometry));
}
