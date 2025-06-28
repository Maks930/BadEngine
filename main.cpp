#include <iostream>

#include <GLFW/glfw3.h>

int main()
{
    if (!glfwInit()) {
        std::cerr << "GLFW not init\n";
        return -1;
    }

    GLFWwindow *win = glfwCreateWindow(640,480,"Test Window", nullptr, nullptr);
    if (!win) {
        glfwTerminate();
        std::cerr << "Failed init window\n";
        return -1;
    }

    glfwMakeContextCurrent(win);

    while (!glfwWindowShouldClose(win)) {
        // glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
