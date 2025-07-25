#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glm/glm.hpp>

#include <Types/Types.h>


class Shader
{
private:
    uint32_t m_id;

public:
    Shader(uint32_t id);
    ~Shader();

    void use();

    static void uniformMatrix(const Shader& shader, const std::string& name, const glm::mat4& matrix);
    static void uniformFloat(const Shader& shader, const std::string& name, const float& number);
    static void uniformVec3(const Shader& shader, const std::string& name, const glm::vec3& vec);

    static Shader* load(const std::string& vertexFile, const std::string& fragmentFile);
};

#endif // SHADER_H
