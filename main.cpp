#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "dependeces/Common/Initialize.h"
#include <glm/glm.hpp>

using namespace glm;



#include "dependeces/Common/shader.hpp"
#include "dependeces/Common/controls.hpp"
#include "src/Clouds.h"
#include "src/ParticlesSystem.h"

int main() {
    GLFWwindow *window;
    window = initGLFW(1024, 768, "triangle", NULL, NULL);
    if (window)
        initGLEW();
    ParticlesSystem app;
    app.setUp(window);


    do {

        app.update(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

    glfwTerminate();
    app.clean(window);

    return 0;
}
