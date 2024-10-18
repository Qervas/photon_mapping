#include "Material.h"

Material::Material() : type(DIFFUSE), color(), refractiveIndex(1.0) {}

Material::Material(MaterialType t, const Color& c, double ri)
    : type(t), color(c), refractiveIndex(ri) {}
