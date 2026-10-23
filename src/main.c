#include "main.h"
#include "renderer.h"
#include "defines.h"

#define WIDTH 800
#define HEIGHT 800

static GLFWwindow* s_window = NULL;

static void svInit(const char* msg)
{
    printf(msg);
    ASSERT(!glfwInit(), "Failed to Load GLFW\n");

    s_window = glfwCreateWindow(WIDTH, HEIGHT, msg, NULL, NULL);
    ASSERT(!s_window, "Failed to Create Window\n");

    glfwMakeContextCurrent(s_window);
    ASSERT(glewInit() != GLEW_OK, "Failed to Load GLEW\n");
}

static void svRun(void(*func)())
{
    while(!glfwWindowShouldClose(s_window))
    {
        glfwPollEvents();

        func();
        glfwSwapBuffers(s_window);
    }
}

static void svTerminate()
{
    glfwDestroyWindow(s_window);
    glfwTerminate();
}

int main(int argc, char** argv)
{
    //Initialize
    svInit("First Opengl Project");

    //Run
    svRun(vRenderFunc);
    
    //Terminate
    svTerminate();
    return 0;
}