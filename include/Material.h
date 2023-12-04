#ifndef MATERIAL_H
#define MATERIAL_H

#include <random>
#include "Ray.h"

class HitResult;

class ReflectResult
{
public:
    Ray m_ray;
    Vector3D m_color;
};

class Material
{
public:
    Vector3D m_color;
    virtual ReflectResult reflect(Ray &ray, HitResult &hit) = 0;
};

class Diffuse : public Material
{
public:
    Diffuse(const Vector3D &color)
    {
        m_color = color;
    };

    virtual ReflectResult reflect(Ray &ray, HitResult &hit) override
    {
        ReflectResult res;
        // TODO: 4. generate one scattered ray and assign it to res.m_ray

        Vector3D r = generate_random_vector3d();
        if (dot(r, hit.m_hitNormal) < 0)
        {
            r = -r;
        }

        res.m_ray = Ray(hit.m_hitPos, r);
        res.m_color = m_color;
        return res;
    }

private:
    Vector3D generate_random_vector3d()
    {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<float> distr(-1.0f, 1.0f);

        Vector3D v;
        v.m_x = distr(eng);
        v.m_y = distr(eng);
        v.m_z = distr(eng);

        return normalize(v);
    }
};

class Specular : public Material
{
public:
    Specular(const Vector3D &color)
    {
        m_color = color;
    }

    virtual ReflectResult reflect(Ray &ray, HitResult &hit) override
    {
        ReflectResult res;
        // TODO: 5. generate one mirrored ray and assign it to res.m_ray

        Vector3D l = ray.direction();
        float t = 2 * dot(l, hit.m_hitNormal);
        Vector3D r = normalize(-l + t * hit.m_hitNormal);

        res.m_ray = Ray(hit.m_hitPos, r);
        res.m_color = m_color;
        return res;
    }
};
#endif
