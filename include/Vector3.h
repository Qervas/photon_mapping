#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
public:
    double x, y, z;

    // Constructors
    Vector3();
    Vector3(double x_, double y_, double z_);

    // Operator overloads
    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator-() const;
    Vector3 operator*(double s) const;
    Vector3 operator/(double s) const;


    // Vector operations
    double dot(const Vector3& v) const;
    Vector3 cross(const Vector3& v) const;
    double length() const;
    Vector3 normalized() const;
};

#endif // VECTOR3_H
