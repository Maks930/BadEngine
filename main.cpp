#include <iostream>
#define GLEW_SHARED
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Core/MountManager/mountmanager.h>
#include <System/Window/window.h>
#include <System/Events/events.h>
#include <Graphics/Shader/shader.h>

float vert2[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

int main()
{

    MountManager::mount("/shaders", std::string(std::getenv("USERPROFILE"))+"\\Desktop\\shaders");


    Window win({640, 480}, "Base Window");


    Shader* shader = Shader::load(rdir("/shaders/main.vert"), rdir("/shaders/main.frag"));

    // glClearColor(1,0.5,0.65,1);
    Events events(&win);
    while (win.isOpen()) {

        if (events.jpressed(GLFW_KEY_ESCAPE)) {
            win.close();
        }

        if (events.jcliced(GLFW_MOUSE_BUTTON_1)) {
            glClearColor(1,0.5,0.65,1);
        } else if (events.jcliced(GLFW_MOUSE_BUTTON_2)) {
            glClearColor(0.25,0.25,0.25,1);
        }

        // shader->use();

        win.swapBuffers();
        win.clear();

        events.pullEvents();
    }

    delete shader;

    return 0;
}
