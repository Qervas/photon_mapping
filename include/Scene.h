#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include <vector>

class Scene {
public:
    std::vector<Object*> objects;

    Scene();
    ~Scene();

    void setupScene();

    bool intersect(const Ray& ray, Intersection& intersection) const;
};

#endif // SCENE_H
