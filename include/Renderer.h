#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "PhotonMap.h"
#include "Color.h"

class Renderer {
public:
    Scene scene;
    PhotonMap globalPhotonMap;

    Renderer();

    void render(int width, int height, const char* filename);
    void emitPhotons(int numPhotons);
    Color radiance(const Ray& ray, int depth);
    void tracePhoton(Photon& photon, int depth);
};

#endif // RENDERER_H
