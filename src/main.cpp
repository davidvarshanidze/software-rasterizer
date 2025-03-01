#include "rasterizer.hpp"

int main() {
    // Create 512x512 image.
    Rasterizer raster(512, 512);
    raster.clear(0x000000);  // Black background.

    // Some sample shapes to show it works.
    raster.drawLine(50, 50, 450, 450, 0xFF0000);  // Red line.
    raster.drawLine(10, 200, 500, 200, 0x00FF00); // Green horizontal line.
    raster.drawLine(256, 10, 256, 500, 0x0000FF); // Blue vertical line.

    // Yellow filled triangle.
    raster.drawTriangle(200, 100, 300, 400, 100, 400, 0xFFFF00);

    // Save the result.
    raster.saveToPPM("output.ppm");
    return 0;
}
