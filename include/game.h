#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "snake.h"
#include "apple.h"

class Game
{
public:
    Game() {}
    int Init(unsigned int width, unsigned int height, const char *title);
    void Run();
    void Clear();
    void ProcessInput();
    bool GridCollisionApple();
    bool OutOfBounds();
    bool keys[1024];
private:
    GLFWwindow *m_window = nullptr;
    unsigned int m_width;
    unsigned int m_height;
    void loadResources();

    Snake *m_snake;
    Apple *m_apple;
};

#endif // GAME_H
