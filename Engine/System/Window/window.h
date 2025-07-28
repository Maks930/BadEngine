#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <Types/Types.h>

#ifndef GL_COLOR_BUFFER_BIT
#define GL_COLOR_BUFFER_BIT 0x4000

#endif //GL_COLOR_BUFFER_BIT
class GLFWwindow;

class Window
{
private:
    static GLFWwindow* m_win;
    static std::string m_title;
    static WinSize m_size;


public:
    //explicit Window(const WinSize& winSize, const std::string& title);
    //~Window();

    static void init(const WinSize& winSize, const std::string& title);

    static void swapBuffers();

    static void clear(const unsigned int& mask = GL_COLOR_BUFFER_BIT);

    static bool isOpen();

    static void close();

    static void setCursorMode(const int& mode);


    static WinSize getSize();

    friend class Events;

};

#endif // WINDOW_H
