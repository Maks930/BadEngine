#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <Types/Types.h>

class Shader
{
private:
    uint32_t m_id;

public:
    Shader(uint32_t id);
    ~Shader();

    void use();


    static Shader* load(const std::string& vertexFile, const std::string& fragmentFile);
};

#endif // SHADER_H
