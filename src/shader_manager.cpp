#include "shader_manager.h"
#include <iostream>

ShaderManager *ShaderManager::sm = nullptr;
std::map<std::string, Shader> ShaderManager::shaders;

ShaderManager *ShaderManager::GetInstance(){
    if(sm == nullptr){
        sm = new ShaderManager();
    }

    return sm;
}

void ShaderManager::LoadShader(std::string key, const char *vertexPath, const char *fragmentPath){
    Shader shader(vertexPath, fragmentPath);
    shaders[key] = shader;
}

Shader &ShaderManager::GetShader(std::string key){
    return shaders[key];
}

ShaderManager::~ShaderManager(){
    for(auto& it : this->shaders){
        it.second.Destroy();
    }
}

void ShaderManager::Destroy(){
    delete sm;
    sm = nullptr;
}
