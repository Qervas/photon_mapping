// PhotonMap.h
#ifndef PHOTONMAP_H
#define PHOTONMAP_H

#include "Photon.h"
#include <vector>

#define ENABLE_KD_TREE

#ifdef ENABLE_KD_TREE
#include "KdTree.h"
#endif

class PhotonMap {
public:
    std::vector<Photon> photons;

    void store(const Photon& photon);

    #ifdef ENABLE_KD_TREE
    KdTree kdTree;
    void build();
    void findPhotons(const Vector3& position, double maxDistance, int maxPhotons, std::vector<Photon>& result) const;
    #else
    std::vector<Photon> findPhotons(const Vector3& position, double maxDistance, int maxPhotons) const;
    #endif
};

#endif // PHOTONMAP_H
