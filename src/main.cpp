#include "Renderer.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(NULL)); // Initialize random seed

    Renderer renderer;
    int width = 4096;
    int height = 4096;
    const char* filename = "output.ppm";

    renderer.render(width, height, filename);

    return 0;
}
