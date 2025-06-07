#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum ID_TYPE
{
    SHADER,
    PROGRAM
};

class Shader
{
public:
    Shader() {};
    Shader(const char *vertexPath, const char *fragmentPath);
    Shader &Use();
    void Destroy();
    void SetMat4(const std::string &name, glm::mat4 matrix);
    void SetVec3(const std::string &name, glm::vec3 value);
private:
    unsigned int m_id;
    void loadShader(const char *vertexPath, const char *fragmentPath);
    std::string readFromFile(const char *filePath);
    void checkErrors(unsigned int id, ID_TYPE type);
};

#endif // SHADER_H
