// Renderer.cpp
#include "Renderer.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#define MAX_PHOTON_DEPTH 5
#define MAX_RAY_DEPTH 5
#define NUM_PHOTONS 200000
#define PHOTON_SEARCH_RADIUS 0.1
#define MAX_PHOTONS_PER_ESTIMATE 50

Renderer::Renderer() {
    scene.setupScene();
}

void Renderer::emitPhotons(int numPhotons) {
    for (int i = 0; i < numPhotons; ++i) {
        // Sample a point on the light source
        Vector3 lightPos = Vector3(0.5, 0.99, -0.5); // Light position
        Vector3 normal = Vector3(0, -1, 0);
        Vector3 dir = randomHemisphereDirection(normal);

        Photon photon;
        photon.position = lightPos;
        photon.direction = dir;
        photon.power = Color(5, 5, 5) * (1.0 / numPhotons); // Total power divided among photons

        tracePhoton(photon, 0);
    }
#ifdef ENABLE_KD_TREE
    globalPhotonMap.build();
#endif
}

void Renderer::tracePhoton(Photon& photon, int depth) {
    if (depth > MAX_PHOTON_DEPTH) return;

    Intersection intersection;
    if (scene.intersect(Ray(photon.position, photon.direction), intersection)) {
        // Store photon if surface is diffuse
        if (intersection.material.type == DIFFUSE) {
            globalPhotonMap.store(Photon(intersection.position, photon.direction, photon.power));
        }

        // Russian roulette termination
        double probability = 0.7;
        if (randomDouble() > probability) return;

        // Scatter photon
        if (intersection.material.type == DIFFUSE) {
            Vector3 newDir = randomHemisphereDirection(intersection.normal);
            photon.position = intersection.position;
            photon.direction = newDir;
            photon.power = photon.power * intersection.material.color * (1.0 / probability);
            tracePhoton(photon, depth + 1);
        } else if (intersection.material.type == SPECULAR) {
            Vector3 reflectDir = photon.direction - intersection.normal * 2.0 * photon.direction.dot(intersection.normal);
            photon.position = intersection.position;
            photon.direction = reflectDir.normalized();
            tracePhoton(photon, depth + 1);
        }
        // Add refractive materials if needed
    }
}

Color Renderer::radiance(const Ray& ray, int depth) {
    if (depth > MAX_RAY_DEPTH) return Color(0, 0, 0);

    Intersection intersection;
    if (scene.intersect(ray, intersection)) {
        // If the material is light source, return its emission
        if (intersection.material.color.r > 10.0) {
            return intersection.material.color;
        }

        if (intersection.material.type == DIFFUSE) {
            // Estimate indirect illumination using photon map
            std::vector<Photon> photons;
            #ifdef ENABLE_KD_TREE
            globalPhotonMap.findPhotons(intersection.position, PHOTON_SEARCH_RADIUS, MAX_PHOTONS_PER_ESTIMATE, photons);
            #else
            photons = globalPhotonMap.findPhotons(intersection.position, PHOTON_SEARCH_RADIUS, MAX_PHOTONS_PER_ESTIMATE);
            #endif

            Color indirect(0, 0, 0);
            for (const Photon& p : photons) {
                double weight = std::max(0.0, intersection.normal.dot(-p.direction));
                indirect += p.power * weight;
            }
            double area = PI * PHOTON_SEARCH_RADIUS * PHOTON_SEARCH_RADIUS;
            indirect = indirect * (0.5 / area); // Scale by area of search radius
            // Direct illumination can be added here if desired
            return indirect * intersection.material.color;
        } else if (intersection.material.type == SPECULAR) {
            Vector3 reflectDir = ray.direction - intersection.normal * 2.0 * ray.direction.dot(intersection.normal);
            return radiance(Ray(intersection.position, reflectDir.normalized()), depth + 1) * intersection.material.color;
        }
        // Add refractive materials if needed
    }

    return Color(0, 0, 0); // Background color
}

void Renderer::render(int width, int height, const char* filename) {
    std::vector<Color> framebuffer(width * height);

    emitPhotons(NUM_PHOTONS);

    // For each pixel
    for (int y = 0; y < height; ++y) {
        std::cerr << "\rRendering line " << y + 1 << " of " << height;
        for (int x = 0; x < width; ++x) {
            // Compute normalized device coordinates
            double ndcX = (x + 0.5) / width;
            double ndcY = (y + 0.5) / height;

            // Generate camera ray (simple pinhole camera)
            Vector3 camPos(0.5, 0.5, 1.5); // Camera position
            Vector3 camDir(ndcX - 0.5, 0.5 - ndcY, -1.0);
            Ray ray(camPos, camDir);

            Color pixelColor = radiance(ray, 0);
            framebuffer[y * width + x] = pixelColor;
        }
    }

    // Save the image to a PPM file
    std::ofstream ofs(filename, std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (const auto& color : framebuffer) {
        double gamma = 2.2;// Gamma correction
        unsigned char r = (unsigned char)(pow(std::min(1.0, color.r), 1.0 / gamma) * 255);
        unsigned char g = (unsigned char)(pow(std::min(1.0, color.g), 1.0 / gamma) * 255);
        unsigned char b = (unsigned char)(pow(std::min(1.0, color.b), 1.0 / gamma) * 255);
        ofs << r << g << b;

    }
    ofs.close();
    std::cerr << "\nRendering complete. Image saved to " << filename << std::endl;
}
