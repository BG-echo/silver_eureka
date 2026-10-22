#include "main.h"
#include "defines.h"


#define WIDTH 600
#define HEIGHT 800

int main(int argc, char** argv)
{
    printf("First Opengl Project\n");
    ASSERT(!glfwInit(), "Failed to Load GLFW\n");

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Opengl", NULL, NULL);
    ASSERT(!window, "Failed to Create Window\n");

    glfwMakeContextCurrent(window);
    ASSERT(glewInit() != GLEW_OK, "Failed to Load GLEW\n");

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}