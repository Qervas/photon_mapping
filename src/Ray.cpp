#include "Ray.h"

Ray::Ray() : origin(), direction() {}
Ray::Ray(const Vector3& o, const Vector3& d) : origin(o), direction(d.normalized()) {}
