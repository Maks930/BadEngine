#include <GLFW/glfw3.h>

#include <Events/events.h>
#include <Window/window.h>



Events::Events(Window *window)
{
    m_current_frame = 0;
    m_frames = std::make_unique<uint32_t[]>(1032);

    m_deltaX = 0;
    m_deltaY = 0;

    m_x = 0;
    m_y = 0;

    m_cursor_locked = false;
    m_cursor_started = false;

    m_win = window;

    glfwSetWindowUserPointer(m_win->m_win, this);

    glfwSetKeyCallback(m_win->m_win, Events::_key_callback);
    glfwSetMouseButtonCallback(m_win->m_win, Events::_mouse_button_callback);
    glfwSetCursorPosCallback(m_win->m_win, Events::_mouse_position_callback);
    glfwSetWindowSizeCallback(m_win->m_win, Events::_window_size_callback);
    glfwSetFramebufferSizeCallback(m_win->m_win, Events::_framebuffer_size_callback);

}

Events::~Events()
{
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

Mouse Events::getMouse() const
{
    return Mouse(m_x, m_y, m_deltaX, m_deltaY, m_cursor_locked, m_cursor_started);
}

void Events::togleCursorVisibility()
{
    m_cursor_locked = !m_cursor_locked;
    m_win->setCursorMode(m_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Events::_key_callback(GLFWwindow *win, int key, int scancode, int action, int mode)
{
    Events* instance = static_cast<Events*>(glfwGetWindowUserPointer(win));

    if (GLFW_PRESS == action) {
        instance->m_keys.set(key, true);
        instance->m_frames[key] = instance->m_current_frame;
    } else if (GLFW_RELEASE) {
        instance->m_keys.set(key, false);
        instance->m_frames[key] = instance->m_current_frame;
    }
}

void Events::_mouse_button_callback(GLFWwindow *window, int button, int action, int mode)
{
    Events* instace = static_cast<Events*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {
        instace->m_keys.set(button + MOUSE_BUTTONS, true);
        instace->m_frames[button + MOUSE_BUTTONS] = instace->m_current_frame;
    }
    else if (action == GLFW_RELEASE) {
        instace->m_keys.set(button + MOUSE_BUTTONS, false);
        instace->m_frames[button + MOUSE_BUTTONS] = instace->m_current_frame;
    }

}

void Events::_mouse_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    Events* instace = static_cast<Events*>(glfwGetWindowUserPointer(window));

    if (instace->m_cursor_started) {
        instace->m_deltaX += xpos - instace->m_x;
        instace->m_deltaY += ypos - instace->m_y;
    }
    else {
        instace->m_cursor_started = true;
    }
    instace->m_x = xpos;
    instace->m_y = ypos;

}

void Events::_window_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0, width, height);
}

void Events::_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
