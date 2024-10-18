#include "Scene.h"
#include "Plane.h"
#include "Sphere.h"

Scene::Scene() {}

Scene::~Scene() {
    for (auto obj : objects) {
        delete obj;
    }
}

void Scene::setupScene() {
    Material redDiffuse(DIFFUSE, Color(0.75, 0.25, 0.25));
    Material greenDiffuse(DIFFUSE, Color(0.25, 0.75, 0.25));
    Material whiteDiffuse(DIFFUSE, Color(0.75, 0.75, 0.75));

    // Left wall
    objects.push_back(new Plane(Vector3(0, 0, 0), Vector3(1, 0, 0), redDiffuse));
    // Right wall
    objects.push_back(new Plane(Vector3(1, 0, 0), Vector3(-1, 0, 0), greenDiffuse));
    // Floor
    objects.push_back(new Plane(Vector3(0, 0, 0), Vector3(0, 1, 0), whiteDiffuse));
    // Ceiling
    objects.push_back(new Plane(Vector3(0, 1, 0), Vector3(0, -1, 0), whiteDiffuse));
    // Back wall
    objects.push_back(new Plane(Vector3(0, 0, -1), Vector3(0, 0, 1), whiteDiffuse));

    // Sphere in the scene
    Material mirror(SPECULAR, Color(0.999, 0.999, 0.999));
    objects.push_back(new Sphere(Vector3(0.5, 0.3, -0.6), 0.2, mirror));

    // Light source as a small plane on the ceiling
    Material lightMat(DIFFUSE, Color(5, 5, 5)); // Intense white light
    objects.push_back(new Plane(Vector3(0.5, 0.99, -0.5), Vector3(0, -1, 0), lightMat));
}

bool Scene::intersect(const Ray& ray, Intersection& intersection) const {
    Intersection tempIntersection;
    bool hitAnything = false;
    double closestT = INFINITY;

    for (const auto& obj : objects) {
        if (obj->intersect(ray, tempIntersection)) {
            if (tempIntersection.t < closestT) {
                closestT = tempIntersection.t;
                intersection = tempIntersection;
                hitAnything = true;
            }
        }
    }

    return hitAnything;
}
