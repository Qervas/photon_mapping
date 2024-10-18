#ifndef UTILITIES_H
#define UTILITIES_H

#include "Vector3.h"
#include <cstdlib>
#include <cmath>

const double PI = 3.14159265358979323846;

double randomDouble();
Vector3 randomHemisphereDirection(const Vector3& normal);

#endif // UTILITIES_H
