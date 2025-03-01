# Software Rasterizer Project

This is a simple **software rasterizer** written in modern C++ (C++17).  
It features:

- ✅ Line drawing (Bresenham algorithm)
- ✅ Triangle rasterization (barycentric method)
- ✅ Image output to `.ppm` (easy to view in any image viewer)

## 🏃‍♂️ Build & Run

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
./bin/rasterizer
```

## Generate

This generates output.ppm, which you can view with:

- macOS Preview (just double-click)
- Linux: feh output.ppm
- Windows: IrfanView or any image viewer that supports PPM
