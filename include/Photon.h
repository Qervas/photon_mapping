#ifndef PHOTON_H
#define PHOTON_H

#include "Vector3.h"
#include "Color.h"

class Photon {
public:
    Vector3 position;
    Vector3 direction; // Incident direction
    Color power;

    Photon();
    Photon(const Vector3& pos, const Vector3& dir, const Color& pow);
};

#endif // PHOTON_H
