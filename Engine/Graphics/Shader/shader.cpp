#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

























