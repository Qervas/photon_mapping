# Photon Mapping Renderer

The implementation includes an optional kd-tree to accelerate photon searches. The images below demonstrate the performance difference when using the kd-tree versus a linear search approach.

<div style="display: flex; justify-content: space-between;">

<div style="text-align: center;">
    <h3>With kd-Tree</h3>
    <img src="img/w_kd.png" alt="With kd-Tree" width="45%">
  </div>

<div style="text-align: center;">
    <h3>Without kd-Tree</h3>
    <img src="img/wo_kd.png" alt="Without kd-Tree" width="45%">
  </div>

</div>

As shown, utilizing a kd-tree significantly enhances rendering performance by reducing the time complexity of photon searches, especially in scenes with a large number of photons.

## Overview

Photon Mapping is a robust global illumination algorithm widely used in realistic rendering applications. This project implements a photon mapping renderer in C++, providing high-quality lighting effects such as caustics, soft shadows, and indirect illumination.

## Features

- **Global Illumination:** Achieve realistic lighting by simulating the behavior of photons as they interact with surfaces.
- **Photon Map Construction:** Efficiently store and retrieve photon information using a custom kd-tree implementation.
- **Scene Management:** Easily set up scenes with various geometric objects, materials, and light sources.
- **Performance Optimization:** Optimize rendering performance with a kd-tree for rapid photon searches.

## Getting Started

### Prerequisites

- **C++17 Compiler:** Ensure you have a C++17 compatible compiler installed.
- **CMake:** Version 3.18 or higher.
- **Build Tools:** Make or any other build system supported by CMake.

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/photon-mapping-renderer.git
   cd photon-mapping-renderer
   ```
2. **Create a Build Directory**

   ```bash
   mkdir build
   cd build
   ```
3. **Run CMake**

   ```bash
   cmake ..
   ```
4. **Build the Project**

   ```bash
   make
   ```
5. **Build Document**
	```bash
	   doxygen Doxyfile
	```


### Usage

After building the project, you can run the renderer with the following command:

```bash
./bin/photon-mapping
```

This will render an image with the default resolution of 4096x4096 pixels and save it as `output.ppm` in the project directory.

The Doxygen document is in `<projectFolder>/doc/html/index.html`.

## Reference

This project is based on the seminal work by Henrik Wann Jensen:

> **Global Illumination using Photon Maps**
> *Rendering Techniques ’96 (Proceedings of the Seventh Eurographics Workshop on Rendering), pages 21–30, 1996*
> **Henrik Wann Jensen**
> Department of Graphical Communication
> The Technical University of Denmark
> [hwj@gk.dtu.dk](mailto:hwj@gk.dtu.dk)
> [http://www.gk.dtu.dk/~hwj](http://www.gk.dtu.dk/~hwj)

For more detailed information, please refer to the original paper.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

*Happy Rendering!*
