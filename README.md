# 🐍 Snake Game (OpenGL)

A simple 2D Snake clone made using OpenGL, created as part of my learning journey into graphics programming.

---

## 🎮 About the Game

This is a classic snake game where player controls snake to collect apples, which help you grow in size. Snake will die if he hits his own tail or border.

Built using:

- C++
- OpenGL (3.3)
- GLFW (for window and input)
- GLM (for math)

---

## 🧰 Dependencies

This project uses the following libraries:

- [GLFW](https://www.glfw.org)
- [GLM](https://github.com/g-truc/glm)

## 🛠️ Building the Project

### Prerequisites

- CMake >= 3.16
- C++17 compatible compiler
- OpenGL development libraries

### Building Instructions

```bash
git clone https://github.com/Jadamka/snake-2d-opengl.git
cd snake-2d-opengl
mkdir build
cd build
cmake ..
make
./SnakeGame
