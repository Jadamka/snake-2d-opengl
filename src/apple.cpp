#include "apple.h"
#include "shader_manager.h"
#include "quad_renderer.h"

#include <random>

void Apple::Init(float scaleX, float scaleY, float red, float green, float blue, unsigned int screenWidth, unsigned int screenHeight){
    this->m_scale = glm::vec2(scaleX, scaleY);
    this->m_color = glm::vec3(red, green, blue);
    this->m_screenWidth = screenWidth;
    this->m_screenHeight = screenHeight;
}

void Apple::SetRandomPosition(Snake *snake){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> xPos(this->m_scale.x/2, this->m_screenWidth-this->m_scale.x/2);
    std::uniform_int_distribution<std::mt19937::result_type> yPos(this->m_scale.y/2, this->m_screenHeight-this->m_scale.y/2);

    std::uniform_int_distribution<std::mt19937::result_type> xCell(0, 9);
    std::uniform_int_distribution<std::mt19937::result_type> yCell(0, 9);

    bool isInsideBodyPart = false;
    do{
        isInsideBodyPart = false;
        int gridX = xCell(rng);
        int gridY = yCell(rng);
        this->m_position = glm::vec2(gridX * this->m_scale.x + this->m_scale.x / 2, gridY * this->m_scale.y + this->m_scale.y / 2);
        glm::ivec2 appleGrid = glm::floor(this->GetPosition() / this->GetScale());
        for(int i = 0; i < snake->m_tails.size(); i++){
            glm::ivec2 snakePart = glm::floor(snake->m_tails[i].currentPosition / snake->GetScale());
            if(appleGrid == snakePart){
                isInsideBodyPart = true;
                break;
            }
        }
    }while(isInsideBodyPart);
}

void Apple::Render(){
    ShaderManager::GetInstance()->GetShader("default").Use();
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(this->m_position, 1.0f));
    model = glm::scale(model, glm::vec3(this->m_scale, 1.0f));
    ShaderManager::GetInstance()->GetShader("default").SetMat4("model", model);
    ShaderManager::GetInstance()->GetShader("default").SetVec3("color", this->m_color);

    QuadRenderer::GetInstance()->Render();
}

glm::vec2 Apple::GetPosition(){
    return this->m_position;
}

glm::vec2 Apple::GetScale(){
    return this->m_scale;
}














