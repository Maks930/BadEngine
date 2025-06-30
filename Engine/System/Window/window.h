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
    GLFWwindow* m_win;
    std::string m_title;
    WinSize m_size;


public:
    explicit Window(const WinSize& winSize, const std::string& title);
    ~Window();

    /** @see glfwSwapBuffers() */
    void swapBuffers();

    /**
     * @see glClear()
     * @param mask is OpenGL mask
     */
    void clear(const unsigned int& mask = GL_COLOR_BUFFER_BIT);

    /** @brief return true if close flag is flase */
    bool isOpen() const;

    /** @brief set close flag; window close automaticly */
    void close();

    void setCursorMode(const int& mode);


    friend class Events;

};

#endif // WINDOW_H
