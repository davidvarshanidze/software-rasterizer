#include "rasterizer.hpp"

int main() {
    Rasterizer raster(512, 512);
    raster.clear(0x000000);

    raster.drawLine(50, 50, 450, 450, 0xFF0000);
    raster.drawLine(10, 200, 500, 200, 0x00FF00);
    raster.drawLine(256, 10, 256, 500, 0x0000FF);

    raster.drawTriangle(200, 100, 300, 400, 100, 400, 0xFFFF00);

    raster.saveToPPM("output.ppm");
    return 0;
}