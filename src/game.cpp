#include "game.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "quad_renderer.h"
#include "shader_manager.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

void Game::ProcessInput(){
    if(glfwGetKey(this->m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(this->m_window, true);
    }

    if(glfwGetKey(this->m_window, GLFW_KEY_W) == GLFW_PRESS){
        this->m_snake->SetDir(UP);
    }
    if(glfwGetKey(this->m_window, GLFW_KEY_S) == GLFW_PRESS){
        this->m_snake->SetDir(DOWN);
    }
    if(glfwGetKey(this->m_window, GLFW_KEY_A) == GLFW_PRESS){
        this->m_snake->SetDir(LEFT);
    }
    if(glfwGetKey(this->m_window, GLFW_KEY_D) == GLFW_PRESS){
        this->m_snake->SetDir(RIGHT);
    }
}

bool Game::GridCollisionApple(){
    glm::ivec2 snakeGrid = glm::floor(this->m_snake->GetPosition() / this->m_snake->GetScale());
    glm::ivec2 appleGrid = glm::floor(this->m_apple->GetPosition() / this->m_apple->GetScale());

    return snakeGrid == appleGrid;
}

bool Game::OutOfBounds(){
    if(this->m_snake->GetPosition().x + this->m_snake->GetScale().x/2 > this->m_width ||
       this->m_snake->GetPosition().x - this->m_snake->GetScale().x/2 < 0 ||
       this->m_snake->GetPosition().y + this->m_snake->GetScale().y/2 > this->m_height ||
       this->m_snake->GetPosition().y - this->m_snake->GetScale().y/2 < 0){
        return true;
    }

    return false;
}

int Game::Init(unsigned int width, unsigned int height, const char *title){
    this->m_width = width;
    this->m_height = height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);
    if(this->m_window == NULL){
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(this->m_window);
    glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize glad!" << std::endl;
        return -1;
    }

    this->loadResources();

    this->m_snake = new Snake();
    this->m_snake->Init(40.0f, 40.0f, 80.0f, 80.0f, 0.0f, 1.0f, 0.0f);

    this->m_apple = new Apple();
    this->m_apple->Init(80.0f, 80.0f, 1.0f, 0.0f, 0.0f, this->m_width, this->m_height);
    this->m_apple->SetRandomPosition(this->m_snake);

    return 0;
}

void Game::loadResources(){
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->m_width), 0.0f, static_cast<float>(this->m_height), -1.0f, 1.0f);
    // SHADERS_DIR defined in CMAKE
    ShaderManager::GetInstance()->LoadShader("default", (SHADERS_DIR + std::string("/shader.vert")).c_str(), (SHADERS_DIR + std::string("/shader.frag")).c_str());

    ShaderManager::GetInstance()->GetShader("default").Use().SetMat4("projection", projection);
}

void Game::Run(){
    const double fpsLimit = 1.0 / 60.0;
    double lastUpdateTime = 0;
    double lastFrameTime = 0;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(!glfwWindowShouldClose(this->m_window)){
        double now = glfwGetTime();
        double deltaTime = now - lastUpdateTime;

        this->ProcessInput();
        glfwPollEvents();

        this->m_snake->Update(deltaTime);
        if(this->GridCollisionApple()){
            this->m_apple->SetRandomPosition(this->m_snake);
            this->m_snake->AddTail();
        }

        if(this->OutOfBounds() || this->m_snake->CollisionTail()){
            // RESTART
            this->m_snake->Init(40.0f, 40.0f, 80.0f, 80.0f, 0.0f, 1.0f, 0.0f);
            this->m_apple->Init(80.0f, 80.0f, 1.0f, 0.0f, 0.0f, this->m_width, this->m_height);
            this->m_apple->SetRandomPosition(this->m_snake);
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if((now - lastFrameTime) >= fpsLimit){
            this->m_snake->Render();
            this->m_apple->Render();

            glfwSwapBuffers(this->m_window);
            lastFrameTime = now;
        }

        lastUpdateTime = now;
    }
}

void Game::Clear(){
    delete m_snake;
    delete m_apple;

    ShaderManager::GetInstance()->Destroy();
    QuadRenderer::GetInstance()->Destroy();
    glfwTerminate();
}










