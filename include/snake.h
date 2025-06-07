#ifndef SNAKE_H
#define SNAKE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Body
{
    glm::vec2 currentPosition;
    // lifeTime is used so collision is not used on tail when its inside snakes, which happens when it spawns
    int lifeTime = 1;
};

class Snake
{
public:
    void Init(float x, float y, float scaleX, float scaleY, float red, float green, float blue);
    void Render();
    void Update(float dt);
    void SetDir(DIRECTION dir);
    void Move();
    glm::vec2 GetPosition();
    glm::vec2 GetScale();
    void AddTail();
    bool CollisionTail();
    std::vector<struct Body> m_tails;
private:
    glm::vec2 m_scale;
    glm::vec3 m_color;
    float m_speed;
    int dx;
    int dy;
    float m_moveTimer;
    float m_moveInterval;
    DIRECTION m_nextDir;
};

#endif // SNAKE_H
