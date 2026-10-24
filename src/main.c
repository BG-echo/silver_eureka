#include "main.h"
#include "renderer.h"
#include "defines.h"

#define WIDTH 800
#define HEIGHT 800

static GLFWwindow* s_window = NULL;

static void svInit(const char* msg, void(*func)())
{
    printf(msg);
    ASSERT(!glfwInit(), , "Failed to Load GLFW\n");

    s_window = glfwCreateWindow(WIDTH, HEIGHT, msg, NULL, NULL);
    ASSERT(!s_window, glfwTerminate(), "Failed to Create Window\n");

    glfwMakeContextCurrent(s_window);
    ASSERT(glewInit() != GLEW_OK, glfwTerminate(), "Failed to Load GLEW\n");

    func();
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

static void svTerminate(void(*func)())
{
    func();

    glfwDestroyWindow(s_window);
    glfwTerminate();
}

int main(int argc, char** argv)
{
    //Initialize
    svInit("First Opengl Project\n", vRenderInit);

    //Run
    svRun(vRenderFunc);
    
    //Terminate
    svTerminate(vRenderTerminate);
    return 0;
}