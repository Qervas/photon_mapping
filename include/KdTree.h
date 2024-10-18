// KdTree.h
#ifndef KDTREE_H
#define KDTREE_H

#include "Photon.h"
#include <vector>
#include <algorithm>
#include <cmath>

// k-d node
struct KdNode {
    Photon photon;
    KdNode* left;
    KdNode* right;

    KdNode(const Photon& p) : photon(p), left(nullptr), right(nullptr) {}
};

class KdTree {
public:
    KdTree();
    ~KdTree();

    void build(std::vector<Photon>& photons);
    void nearestPhotons(const Vector3& position, double maxDistance, int maxPhotons, std::vector<Photon>& result) const;

private:
    KdNode* root;
    KdNode* buildRecursive(std::vector<Photon>& photons, int depth, int start, int end);
    void searchRecursive(KdNode* node, const Vector3& position, double maxDistance, int maxPhotons, int depth, std::vector<Photon>& result) const;
    void destroyRecursive(KdNode* node);
};

#endif // KDTREE_H
