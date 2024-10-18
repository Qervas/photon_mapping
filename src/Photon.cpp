#include "Photon.h"

Photon::Photon() : position(), direction(), power() {}
Photon::Photon(const Vector3& pos, const Vector3& dir, const Color& pow)
    : position(pos), direction(dir), power(pow) {}
