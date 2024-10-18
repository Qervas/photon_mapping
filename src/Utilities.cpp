#include "Utilities.h"

double randomDouble() {
    return rand() / (RAND_MAX + 1.0);
}

Vector3 randomHemisphereDirection(const Vector3& normal) {
    double u = randomDouble();
    double v = randomDouble();
    double theta = acos(sqrt(1.0 - u));
    double phi = 2.0 * PI * v;

    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);

    Vector3 dir(x, y, z);
    if (dir.dot(normal) < 0)
        dir = dir * -1.0; // Ensure it's in the same hemisphere
    return dir.normalized();
}
