#include "events.h"
#include <GLFW/glfw3.h>

#include <Events/events.h>
#include <Window/window.h>


std::bitset<1032>               Events::m_keys{};
std::unique_ptr<uint32_t[]>     Events::m_frames = std::make_unique<uint32_t[]>(1032);
uint32_t                        Events::m_current_frame{0};
double                          Events::m_deltaX{0};
double                          Events::m_deltaY{0};
double                          Events::m_x{0};
double                          Events::m_y{0};
bool                            Events::m_cursor_locked{false};
bool                            Events::m_cursor_started{false};




void Events::init()
{
    
    glfwSetKeyCallback(Window::m_win, Events::_key_callback);
    glfwSetMouseButtonCallback(Window::m_win, Events::_mouse_button_callback);
    glfwSetCursorPosCallback(Window::m_win, Events::_mouse_position_callback);
    glfwSetWindowSizeCallback(Window::m_win, Events::_window_size_callback);
    glfwSetFramebufferSizeCallback(Window::m_win, Events::_framebuffer_size_callback);
}

void Events::pullEvents()
{
    m_current_frame++;
    m_deltaX = 0.0;
    m_deltaY = 0.0;

    glfwPollEvents();
}

bool Events::jpressed(const int &keycode)
{
    if (keycode < 0 || keycode >= MOUSE_BUTTONS) {
        return false;
    }

    return m_keys.test(keycode)
           && m_frames[keycode] == m_current_frame;
}

bool Events::ipressed(const int &keycode)
{
    if (keycode < 0 || keycode >= MOUSE_BUTTONS) {
        return false;
    }

    return m_keys.test(keycode);
}

bool Events::icliced(const int &button)
{
    int index = MOUSE_BUTTONS + button;
    return m_keys.test(index);
}

bool Events::jcliced(const int &button)
{
    int index = MOUSE_BUTTONS + button;

    return m_keys.test(index)
           && m_frames[index] == m_current_frame;
}

Mouse Events::getMouse()
{
    return Mouse(m_x, m_y, m_deltaX, m_deltaY, m_cursor_locked, m_cursor_started);
}

void Events::togleCursorVisibility()
{
    m_cursor_locked = !m_cursor_locked;
    Window::setCursorMode(m_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Events::_key_callback(GLFWwindow *win, int key, int scancode, int action, int mode)
{

    if (GLFW_PRESS == action) {
        Events::m_keys.set(key, true);
        Events::m_frames[key] = Events::m_current_frame;
    } else if (GLFW_RELEASE == action) {
        Events::m_keys.set(key, false);
        Events::m_frames[key] = Events::m_current_frame;
    }
}

void Events::_mouse_button_callback(GLFWwindow *window, int button, int action, int mode)
{
    if (action == GLFW_PRESS) {
         Events::m_keys.set(button + MOUSE_BUTTONS, true);
         Events::m_frames[button + MOUSE_BUTTONS] = Events::m_current_frame;
    }
    else if (action == GLFW_RELEASE) {
         Events::m_keys.set(button + MOUSE_BUTTONS, false);
         Events::m_frames[button + MOUSE_BUTTONS] = Events::m_current_frame;
    }

}

void Events::_mouse_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (Events::m_cursor_started) {
         Events::m_deltaX += xpos - Events::m_x;
         Events::m_deltaY += ypos - Events::m_y;
    }
    else {
        Events::m_cursor_started = true;
    }
     Events::m_x = xpos;
     Events::m_y = ypos;

}

void Events::_window_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0, width, height);
}

void Events::_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
