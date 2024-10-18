#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
public:
    Vector3 center;
    double radius;

    Sphere(const Vector3& c, double r, const Material& m);

    bool intersect(const Ray& ray, Intersection& intersection) const override;
};

#endif // SPHERE_H
