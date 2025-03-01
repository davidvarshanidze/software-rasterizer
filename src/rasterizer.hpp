#pragma once // Just a cleaner way to prevent double inclusion of this file.

#include <vector>  // We use this for our framebuffer.
#include <cstdint> // For fixed-size uint32_t.
#include <string>  // So we can pass file names.

class Rasterizer
{
public:
    // Constructor — takes the width & height of the image we're drawing.
    Rasterizer(int width, int height);

    // Clears the entire framebuffer to a single color.
    void clear(uint32_t color);

    // Set a single pixel to a color.
    void setPixel(int x, int y, uint32_t color);

    // Draws a line between two points (x0, y0) to (x1, y1).
    void drawLine(int x0, int y0, int x1, int y1, uint32_t color);

    // Draws a filled triangle given 3 vertices.
    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

    // Saves the framebuffer to a .ppm image file.
    void saveToPPM(const std::string &filename) const;

private:
    int width, height;                 // Image dimensions.
    std::vector<uint32_t> framebuffer; // The actual pixel data.

    // Helper to check if a point (x, y) is inside a triangle.
    bool isInsideTriangle(int x, int y,
                          int x0, int y0,
                          int x1, int y1,
                          int x2, int y2);
};
