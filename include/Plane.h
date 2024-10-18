#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object {
public:
    Vector3 point;
    Vector3 normal;

    Plane(const Vector3& p, const Vector3& n, const Material& m);

    bool intersect(const Ray& ray, Intersection& intersection) const override;
};

#endif // PLANE_H
