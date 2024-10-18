#include "KdTree.h"

KdTree::KdTree() : root(nullptr) {}

// destory k-d tree
KdTree::~KdTree() {
    destroyRecursive(root);
}

// build k-d tree
void KdTree::build(std::vector<Photon>& photons) {
    root = buildRecursive(photons, 0, 0, photons.size());
}

// build k-d recursively
KdNode* KdTree::buildRecursive(std::vector<Photon>& photons, int depth, int start, int end) {
    if (start >= end) return nullptr;

    int axis = depth % 3; // select axis: ：0=x, 1=y, 2=z
    int mid = start + (end - start) / 2;

    // sort photons by axis
    auto comparator = [axis](const Photon& a, const Photon& b) -> bool {
        if (axis == 0)
            return a.position.x < b.position.x;
        else if (axis == 1)
            return a.position.y < b.position.y;
        else
            return a.position.z < b.position.z;
    };

    std::nth_element(photons.begin() + start, photons.begin() + mid, photons.begin() + end, comparator);

    // create node
    KdNode* node = new KdNode(photons[mid]);

    // recursively build left and right subtree
    node->left = buildRecursive(photons, depth + 1, start, mid);
    node->right = buildRecursive(photons, depth + 1, mid + 1, end);

    return node;
}

// find nearest photons
void KdTree::nearestPhotons(const Vector3& position, double maxDistance, int maxPhotons, std::vector<Photon>& result) const {
    searchRecursive(root, position, maxDistance, maxPhotons, 0, result);
}

// search photons recursively
void KdTree::searchRecursive(KdNode* node, const Vector3& position, double maxDistance, int maxPhotons, int depth, std::vector<Photon>& result) const {
    if (node == nullptr) return;

    double distance2 = (node->photon.position - position).length();
    if (distance2 <= maxDistance) {
        result.push_back(node->photon);
        if (result.size() >= maxPhotons)
            return;
    }

    int axis = depth % 3;
    double diff;
    if (axis == 0)
        diff = position.x - node->photon.position.x;
    else if (axis == 1)
        diff = position.y - node->photon.position.y;
    else
        diff = position.z - node->photon.position.z;

    KdNode* first = (diff < 0) ? node->left : node->right;
    KdNode* second = (diff < 0) ? node->right : node->left;

    // search the nearest subtree first
    searchRecursive(first, position, maxDistance, maxPhotons, depth + 1, result);

    // if the other subtree may contain photons closer than the farthest photon found so far
    if (std::abs(diff) <= maxDistance && result.size() < maxPhotons) {
        searchRecursive(second, position, maxDistance, maxPhotons, depth + 1, result);
    }
}

// destroy k-d tree recursively
void KdTree::destroyRecursive(KdNode* node) {
    if (node == nullptr) return;
    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
}
