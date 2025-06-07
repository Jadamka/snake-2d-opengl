#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "shader.h"
#include <string>
#include <map>

class ShaderManager
{
public:
    static ShaderManager *GetInstance();
    ~ShaderManager();
    static void LoadShader(std::string key, const char *vertexPath, const char *fragmentPath);
    static Shader &GetShader(std::string key);
    static void Destroy();
private:
    static ShaderManager *sm;
    ShaderManager() {}
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;
    static std::map<std::string, Shader> shaders;
};

#endif // SHADER_MANAGER_H
