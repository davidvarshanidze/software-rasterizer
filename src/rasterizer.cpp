#include "rasterizer.hpp"
#include <fstream>    // For writing the PPM file.
#include <iostream>   // To log errors.
#include <algorithm>  // For min/max.

Rasterizer::Rasterizer(int width, int height)
    : width(width), height(height), framebuffer(width * height, 0x00000000) {}  // Start with black (0x000000).

void Rasterizer::clear(uint32_t color) {
    // Fill the entire framebuffer with the given color.
    std::fill(framebuffer.begin(), framebuffer.end(), color);
}

void Rasterizer::setPixel(int x, int y, uint32_t color) {
    // Only set pixels that are inside the image boundaries.
    if (x >= 0 && x < width && y >= 0 && y < height) {
        framebuffer[y * width + x] = color;  // Map 2D to 1D.
    }
}

void Rasterizer::drawLine(int x0, int y0, int x1, int y1, uint32_t color) {
    // Bresenham's line algorithm, works for any slope.

    // Check if line is steep (more vertical than horizontal).
    bool steep = false;
    if (std::abs(y1 - y0) > std::abs(x1 - x0)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    // Make sure we're always drawing left to right.
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = std::abs(y1 - y0);
    int error = dx / 2;  // Keeps track of how "off" we are.
    int ystep = (y0 < y1) ? 1 : -1;  // Direction of Y.
    int y = y0;

    for (int x = x0; x <= x1; ++x) {
        if (steep) setPixel(y, x, color);  // Swap back for steep lines.
        else setPixel(x, y, color);

        error -= dy;
        if (error < 0) {
            y += ystep;  // Move Y when error gets too high.
            error += dx;
        }
    }
}

void Rasterizer::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // Find bounding box — only loop over the triangle's area.
    int minX = std::min({x0, x1, x2});
    int maxX = std::max({x0, x1, x2});
    int minY = std::min({y0, y1, y2});
    int maxY = std::max({y0, y1, y2});

    // Check every pixel inside the bounding box.
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            // If the pixel is inside the triangle, color it.
            if (isInsideTriangle(x, y, x0, y0, x1, y1, x2, y2)) {
                setPixel(x, y, color);
            }
        }
    }
}

// Check if a point is inside the triangle using the edge function method.
bool Rasterizer::isInsideTriangle(int x, int y, 
                                  int x0, int y0, 
                                  int x1, int y1, 
                                  int x2, int y2) {
    // Helper lambda to calculate signed area (determinant style).
    auto edgeFunction = [](int x0, int y0, int x1, int y1, int x, int y) -> int {
        return (x - x0) * (y1 - y0) - (y - y0) * (x1 - x0);
    };

    // Point is inside if it's on the correct side of all 3 edges.
    return edgeFunction(x0, y0, x1, y1, x, y) >= 0 &&
           edgeFunction(x1, y1, x2, y2, x, y) >= 0 &&
           edgeFunction(x2, y2, x0, y0, x, y) >= 0;
}

void Rasterizer::saveToPPM(const std::string& filename) const {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    // Write the PPM header.
    file << "P6\n" << width << " " << height << "\n255\n";

    // Write each pixel (24-bit RGB).
    for (auto pixel : framebuffer) {
        uint8_t r = (pixel >> 16) & 0xFF;
        uint8_t g = (pixel >> 8) & 0xFF;
        uint8_t b = (pixel) & 0xFF;
        file.write(reinterpret_cast<char*>(&r), 1);
        file.write(reinterpret_cast<char*>(&g), 1);
        file.write(reinterpret_cast<char*>(&b), 1);
    }
}
