# NetRoute

A small C++ project that shows a network of routers on screen and finds the shortest path using **Dijkstra's algorithm**. Built with **SFML** for the graphics.

## What it does

- Draws routers as circles and links between them as lines
- Edge weights are shown on the links (like latency)
- Highlights the shortest path from **R-A** to **R-F** in green (edges) and orange (nodes)

## Requirements (Mac)

- C++ compiler (Xcode Command Line Tools)
- [Homebrew](https://brew.sh)
- SFML 2 and CMake:

```bash
brew install sfml@2 cmake
```

If you also have SFML 3 installed, unlink it so the project uses SFML 2:

```bash
brew unlink sfml
```

## How to build and run

```bash
cd NetRoute
mkdir -p build
cd build
cmake ..
cmake --build .
./NetRoute
```

Run `./NetRoute` from the `build` folder so the font in `assets/` loads correctly.

Close the window when you are done.

## Project structure

```
NetRoute/
├── src/          # .cpp source files (main, Graph, Dijkstra, Visualizer)
├── include/      # header files
├── assets/       # font file for labels
├── CMakeLists.txt
└── README.md
```

## Push to GitHub (quick steps)

```bash
git init
git add .
git commit -m "Initial commit"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/NetRoute.git
git push -u origin main
```

Replace `YOUR_USERNAME` with your GitHub username.

## Author

Third-year project — network routing visualizer.
