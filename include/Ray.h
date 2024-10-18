#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray {
public:
    Vector3 origin;
    Vector3 direction;

    Ray();
    Ray(const Vector3& o, const Vector3& d);
};

#endif // RAY_H
