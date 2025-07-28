#include "window.h"
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Window/window.h>

GLFWwindow* Window::m_win = nullptr;
std::string Window::m_title = "";
WinSize Window::m_size = {0,0};

void Window::init(const WinSize& winSize, const std::string& title)
{
    m_title = title;
    m_size = winSize;
    if (!glfwInit()) {
        abort();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    m_win = glfwCreateWindow(m_size.width, m_size.height, title.c_str(), nullptr, nullptr);

    if (!m_win) {
        glfwTerminate();
        abort();
    }

    glfwMakeContextCurrent(m_win);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glViewport(0, 0, winSize.width, winSize.height);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_win);
}

void Window::clear(const unsigned int &mask)
{

    glClear(mask);
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(m_win);
}

void Window::close()
{
    glfwSetWindowShouldClose(m_win, true);
}

void Window::setCursorMode(const int &mode)
{
    glfwSetInputMode(m_win, GLFW_CURSOR, mode);
}

WinSize Window::getSize()
{
    return m_size;
}
