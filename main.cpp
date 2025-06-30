#include <iostream>
#include <GLFW/glfw3.h>

#include <Core/MountManager/mountmanager.h>
#include <System/Window/window.h>
#include <System/Events/events.h>
#include <Core/Color/color.h>


int main()
{

    Window win({640, 480}, "Base Window");
    Events events(&win);

    Color c(175, 255, 55, 98);

    std::cout << (int)c.red << std::endl;
    std::cout << (int)c.green << std::endl;
    std::cout << (int)c.blue << std::endl;
    std::cout << (int)c.alpha << std::endl;


    // glClearColor(1,0.5,0.65,1);

    while (win.isOpen()) {

        if (events.jpressed(GLFW_KEY_ESCAPE)) {
            win.close();
        }

        if (events.jcliced(GLFW_MOUSE_BUTTON_1)) {
            glClearColor(1,0.5,0.65,1);
        } else if (events.jcliced(GLFW_MOUSE_BUTTON_2)) {
            glClearColor(0.25,0.25,0.25,1);
        }

        win.swapBuffers();
        win.clear();

        events.pullEvents();
    }

    return 0;
}
