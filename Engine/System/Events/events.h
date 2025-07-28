#ifndef EVENTS_H
#define EVENTS_H

#include <bitset>
#include <memory>

#include <Types/Types.h>

#define MOUSE_BUTTONS 1024
class Window;
class GLFWwindow;

class Events
{
private:
    static std::bitset<1032>               m_keys;
    static std::unique_ptr<uint32_t[]>     m_frames;
    static uint32_t                        m_current_frame;
    static double                          m_deltaX;
    static double                          m_deltaY;
    static double                          m_x;
    static double                          m_y;
    static bool                            m_cursor_locked;
    static bool                            m_cursor_started;

public:
    static void init();
      
    static void pullEvents();

    static bool jpressed(const int& keycode);
    static bool ipressed(const int& keycode);

    static bool icliced(const int& button);
    static bool jcliced(const int& button);

    static Mouse getMouse();

    static void togleCursorVisibility();


private: // CallBacks
    static void _key_callback(GLFWwindow* win, int key, int scancode, int action, int mode);
    static void _mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
    static void _mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void _window_size_callback(GLFWwindow* window, int width, int height);
    static void _framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif // EVENTS_H
