#include "shader.h"

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char *vertexPath, const char *fragmentPath){
    this->loadShader(vertexPath, fragmentPath);
}

void Shader::loadShader(const char *vertexPath, const char *fragmentPath){
    std::string vertexSourceStr = this->readFromFile(vertexPath);
    std::string fragmentSourceStr = this->readFromFile(fragmentPath);

    const char *vertexSource = vertexSourceStr.c_str();
    const char *fragmentSource = fragmentSourceStr.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    this->checkErrors(vertex, SHADER);

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    this->checkErrors(fragment, SHADER);

    this->m_id = glCreateProgram();
    glAttachShader(this->m_id, vertex);
    glAttachShader(this->m_id, fragment);
    glLinkProgram(this->m_id);
    this->checkErrors(this->m_id, PROGRAM);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

std::string Shader::readFromFile(const char *filePath){
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream buffer;

    try{
        file.open(filePath);
        buffer << file.rdbuf();
    }
    catch(const std::exception &e){
        std::cerr << "Reading from file went wrong! File path: " << filePath << " | " << e.what() << std::endl;
        return "";
    }

    return buffer.str();
}

void Shader::checkErrors(unsigned int id, ID_TYPE type){
    int success;
    char infoLog[1024];

    if(type == SHADER){
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(id, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER\n" << infoLog << std::endl;
        }
    }
    else if(type == PROGRAM){
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM\n" << infoLog << std::endl;
        }
    }
}

Shader &Shader::Use(){
    glUseProgram(this->m_id);
    return *this;
}

void Shader::SetMat4(const std::string &name, glm::mat4 matrix){
    glUniformMatrix4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVec3(const std::string &name, glm::vec3 value){
    glUniform3f(glGetUniformLocation(this->m_id, name.c_str()), value.x, value.y, value.z);
}

void Shader::Destroy(){
    glDeleteProgram(this->m_id);
}

















