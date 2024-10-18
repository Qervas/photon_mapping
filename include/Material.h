#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

enum MaterialType { DIFFUSE, SPECULAR, REFRACTIVE };

class Material {
public:
    MaterialType type;
    Color color;
    double refractiveIndex; // For refractive materials

    Material();
    Material(MaterialType t, const Color& c, double ri = 1.0);
};

#endif // MATERIAL_H
