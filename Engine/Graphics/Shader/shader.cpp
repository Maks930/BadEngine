#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/ext.hpp>

#include <Shader/shader.h>




Shader::Shader(uint32_t id) : m_id(id) {}

Shader::~Shader()
{
    glDeleteShader(m_id);
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::uniformMatrix(const Shader &shader, const std::string &name, const glm::mat4 &matrix)
{
    GLuint transformLoc = glGetUniformLocation(shader.m_id, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::uniformVec3(const Shader& shader, const std::string& name, const glm::vec3& vec) 
{
    GLuint transformLoc = glGetUniformLocation(shader.m_id, name.c_str());
    glUniform3fv(transformLoc, 1, glm::value_ptr(vec));
}

void Shader::uniformFloat(const Shader &shader, const std::string &name, const float &number)
{
    GLuint transformLoc = glGetUniformLocation(shader.m_id, name.c_str());
    glUniform1f(transformLoc, number);
}

Shader *Shader::load(const std::string &vertexFile, const std::string &fragmentFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);

    try {
        vShaderFile.open(vertexFile);
        fShaderFile.open(fragmentFile);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERR:SHADER::FILE_NOT_SUCCESFULLY_READ\n";
        return nullptr;
    }


    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "SHADER::VERTEX: compilation failed\n";
        std::cerr << infoLog << std::endl;
        return nullptr;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "SHADER::FRAGMENT: compilation failed\n";
        std::cerr << infoLog << std::endl;
        return nullptr;
    }

    GLuint id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "SHADER::PROGRAM: linking failed\n";
        std::cerr << infoLog << std::endl;

        glDeleteProgram(id);
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return nullptr;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);


    return new Shader(id);
}

























