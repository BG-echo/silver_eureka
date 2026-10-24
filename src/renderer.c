#include "glew.h"

#include "stdio.h"
#include "stdlib.h"

#include "renderer.h"
#include "shader.h"
#include "shapes.h"

struct 
{
    Shader* sShader;
    Container* container;
}sRenderer;

void vRenderInit()
{
    float vertices[18] = 
    {
        // positions          
         0.5f,  0.5f, 0.0f,   
         0.5f, -0.5f, 0.0f,   
        -0.5f, -0.5f, 0.0f,   
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,   
    };
        
    float color[18] = 
    {
        0.5f, 0.2f, 0.6f,
        0.5f, 0.2f, 0.6f,
        0.5f, 0.2f, 0.6f,
        0.5f, 0.2f, 0.6f,
        0.5f, 0.2f, 0.6f,
        0.5f, 0.2f, 0.6f,
    };
    sRenderer.sShader = sCreateShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    vCreateContainer(&sRenderer.container, vertices, color, "../bin/textures/wall.jpg");

    vUseShader(sRenderer.sShader);
    vShaderSetInt(sRenderer.sShader, "tex", 0);
}

void vRenderFunc()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vUseShader(sRenderer.sShader);
    glBindVertexArray(sRenderer.container->GObject->m_uVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void vRenderTerminate()
{
    vDestroyShader(sRenderer.sShader);
}