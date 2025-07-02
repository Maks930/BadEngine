#ifndef SHADER_H
#define SHADER_H


#include <cstdint>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader {
private:
    uint32_t _id;
public:
    Shader(uint32_t id);
    ~Shader();

    void use();
    void uniformMatrix(std::string name, glm::mat4 matrix);
    void uniformFloat(std::string name, float number);
};

extern Shader* load_shader(std::string vertexFile, std::string fragmentFile);


#endif // SHADER_H
