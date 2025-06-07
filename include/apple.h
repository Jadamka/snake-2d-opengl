#ifndef APPLE_H
#define APPLE_H

#include "snake.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Apple
{
public:
    void Init(float scaleX, float scaleY, float red, float green, float blue, unsigned int screenWidth, unsigned int screenHeight);
    void Render();
    void SetRandomPosition(Snake *snake);
    glm::vec2 GetPosition();
    glm::vec2 GetScale();
private:
    glm::vec2 m_position;
    glm::vec2 m_scale;
    glm::vec3 m_color;
    unsigned int m_screenWidth;
    unsigned int m_screenHeight;
};

#endif // APPLE_H
