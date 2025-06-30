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
    std::bitset<1032>               m_keys;
    std::unique_ptr<uint32_t[]>     m_frames;
    uint32_t                        m_current_frame;
    double                          m_deltaX;
    double                          m_deltaY;
    double                          m_x;
    double                          m_y;
    bool                            m_cursor_locked;
    bool                            m_cursor_started;

    Window*                         m_win;



public:
    Events(Window* window);
    ~Events();

    void pullEvents();

    bool jpressed(const int& keycode);
    bool ipressed(const int& keycode);

    bool icliced(const int& button);
    bool jcliced(const int& button);

    Mouse getMouse() const;

    void togleCursorVisibility();


private: // CallBacks
    static void _key_callback(GLFWwindow* win, int key, int scancode, int action, int mode);
    static void _mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
    static void _mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void _window_size_callback(GLFWwindow* window, int width, int height);
    static void _framebuffer_size_callback(GLFWwindow* window, int width, int height);


};

#endif // EVENTS_H
