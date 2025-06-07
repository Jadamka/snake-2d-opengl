#include "snake.h"
#include "shader_manager.h"
#include "quad_renderer.h"
#include <iostream>

void Snake::Init(float x, float y, float scaleX, float scaleY, float red, float green, float blue){
    struct Body head;
    head.currentPosition = glm::vec2(x, y);
    this->m_scale = glm::vec2(scaleX, scaleY);
    this->m_color = glm::vec3(red, green, blue);
    this->m_speed = 200.0f;
    this->dx = 0;
    this->dy = 0;
    this->m_nextDir = UP;
    this->m_moveTimer = 0.0f;
    this->m_moveInterval = 0.3f;

    this->m_tails.clear();
    this->m_tails.insert(this->m_tails.end(), head);
}

void Snake::SetDir(DIRECTION dir){
    this->m_nextDir = dir;
}

void Snake::Move(){
    switch(this->m_nextDir){
    case UP:
        if(this->dy != -1){
            this->dx = 0;
            this->dy = 1;
        }
        break;
    case DOWN:
        if(this->dy != 1){
            this->dx = 0;
            this->dy = -1;
        }
        break;
    case LEFT:
        if(this->dx != 1){
            this->dx = -1;
            this->dy = 0;
        }
        break;
    case RIGHT:
        if(this->dx != - 1){
            this->dx = 1;
            this->dy = 0;
        }
        break;
    default:
        break;
    }
}

void Snake::Render(){
    for(auto &body : this->m_tails){
        ShaderManager::GetInstance()->GetShader("default").Use();
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(body.currentPosition, 1.0f));
        model = glm::scale(model, glm::vec3(this->m_scale, 1.0f));
        ShaderManager::GetInstance()->GetShader("default").SetMat4("model", model);
        ShaderManager::GetInstance()->GetShader("default").SetVec3("color", this->m_color);

        QuadRenderer::GetInstance()->Render();
    }
}

void Snake::Update(float dt){
    this->m_moveTimer += dt;
    if(this->m_moveTimer < this->m_moveInterval){
        return;
    }

    this->m_moveTimer = 0.0f;
    this->Move();

    for(int i = m_tails.size() - 1; i > 0; i--){
        this->m_tails[i].currentPosition = this->m_tails[i-1].currentPosition;
        if(this->m_tails[i].lifeTime > 0){
            this->m_tails[i].lifeTime--;
        }
    }

    this->m_tails[0].currentPosition.x += this->dx * this->m_scale.x;
    this->m_tails[0].currentPosition.y += this->dy * this->m_scale.y;
}

glm::vec2 Snake::GetPosition(){
    return this->m_tails[0].currentPosition;
}

glm::vec2 Snake::GetScale(){
    return this->m_scale;
}

void Snake::AddTail(){
    struct Body tail;
    tail.currentPosition = this->m_tails[this->m_tails.size()-1].currentPosition;
    this->m_tails.insert(this->m_tails.end(), tail);
}

bool Snake::CollisionTail(){
    glm::ivec2 snakeGrid = glm::floor(this->GetPosition() / this->GetScale());

    for(int i = 1; i < this->m_tails.size(); i++){
        glm::ivec2 tailGrid = glm::floor(this->m_tails[i].currentPosition / this->GetScale());
        if(snakeGrid == tailGrid && this->m_tails[i].lifeTime == 0){
            return true;
        }
    }

    return false;
}




















