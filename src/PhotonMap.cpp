#include "PhotonMap.h"
#include <cmath>

void PhotonMap::store(const Photon& photon) {
    photons.push_back(photon);
}

#ifdef ENABLE_KD_TREE
void PhotonMap::build() {
    kdTree.build(photons);
}

void PhotonMap::findPhotons(const Vector3& position, double maxDistance, int maxPhotons, std::vector<Photon>& result) const {
    kdTree.nearestPhotons(position, maxDistance, maxPhotons, result);
}

#else
std::vector<Photon> PhotonMap::findPhotons(const Vector3& position, double maxDistance, int maxPhotons) const {
    std::vector<Photon> found;
    for (const Photon& p : photons) {
        double dist2 = (p.position - position).length();
        if (dist2 <= maxDistance) {
            found.push_back(p);
            if (found.size() >= maxPhotons)
                break;
        }
    }
    return found;
}
#endif
