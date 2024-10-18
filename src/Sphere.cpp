#include "Sphere.h"

Sphere::Sphere(const Vector3& c, double r, const Material& m) {
    center = c;
    radius = r;
    material = m;
}

bool Sphere::intersect(const Ray& ray, Intersection& intersection) const {
    Vector3 oc = ray.origin - center;
    double b = oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - c;
    if (discriminant > 0) {
        double sqrtDisc = sqrt(discriminant);
        double t1 = -b - sqrtDisc;
        double t2 = -b + sqrtDisc;
        double t = (t1 > 1e-6) ? t1 : ((t2 > 1e-6) ? t2 : 0);
        if (t > 1e-6) {
            intersection.happened = true;
            intersection.t = t;
            intersection.position = ray.origin + ray.direction * t;
            intersection.normal = (intersection.position - center).normalized();
            intersection.material = material;
            return true;
        }
    }
    return false;
}
