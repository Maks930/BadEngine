#include <GLFW/glfw3.h>

#include <Window/window.h>


Window::Window(const WinSize &winSize, const std::string &title) :
    m_size(winSize),
    m_title(title)
{

    if (!glfwInit()) {
        abort();
    }

    m_win = glfwCreateWindow(m_size.width, m_size.height, title.c_str(), nullptr, nullptr);

    if (!m_win) {
        glfwTerminate();
        abort();
    }

    glfwMakeContextCurrent(m_win);

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
