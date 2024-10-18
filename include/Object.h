#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "Material.h"

class Intersection {
public:
    bool happened;
    double t;
    Vector3 position;
    Vector3 normal;
    Material material;

    Intersection() : happened(false), t(0), position(), normal(), material() {}
};

class Object {
public:
    Material material;

    virtual bool intersect(const Ray& ray, Intersection& intersection) const = 0;
};

#endif // OBJECT_H
