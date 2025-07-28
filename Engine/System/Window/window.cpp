#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Window/window.h>


Window::Window(const WinSize &winSize, const std::string &title) :
    m_size(winSize),
    m_title(title)
{

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

Window::~Window()
{
    glfwTerminate();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_win);
}

void Window::clear(const unsigned int &mask)
{

    glClear(mask);
}

bool Window::isOpen() const
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

WinSize Window::getSize() const
{
    return m_size;
}
