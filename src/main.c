#include "main.h"

#define WIDTH 600
#define HEIGHT 800

int main(int argc, char** argv)
{
    printf("First Opengl Project");

    if(!glfwInit())
        exit(1);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Opengl", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    if(glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

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