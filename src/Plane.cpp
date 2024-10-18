#include "Plane.h"

Plane::Plane(const Vector3& p, const Vector3& n, const Material& m) {
    point = p;
    normal = n.normalized();
    material = m;
}

bool Plane::intersect(const Ray& ray, Intersection& intersection) const {
    double denom = normal.dot(ray.direction);
    if (fabs(denom) > 1e-6) {
        double t = (point - ray.origin).dot(normal) / denom;
        if (t >= 1e-6) {
            intersection.happened = true;
            intersection.t = t;
            intersection.position = ray.origin + ray.direction * t;
            intersection.normal = normal;
            intersection.material = material;
            return true;
        }
    }
    return false;
}
