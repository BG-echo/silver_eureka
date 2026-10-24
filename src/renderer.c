#include "glew.h"
#include "renderer.h"
#include "shader.h"

typedef struct sTriangle 
{
    float* m_fVertices;
    float* m_fColor;

    unsigned int m_uVAO;
    unsigned int m_uVBO[2];
}Triangle;

struct 
{
    Shader* sShader;
    Triangle triangle;
}sRenderer;

static void svDrawTriangle(Triangle* t, float* vertices, float* color)
{    
    t->m_fVertices = vertices;
    t->m_fColor = color;
    
    glGenBuffers(1, &t->m_uVAO);
    glGenBuffers(2, t->m_uVBO);
    
    glBindVertexArray(t->m_uVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, t->m_uVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), t->m_fVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, t->m_uVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), t->m_fColor, GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void vRenderInit()
{
    float vertices[9] = 
    {
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
        
    float color[9] = 
    {
        0.5f, 0.2f, 0.6f,
        0.5f, 0.2f, 0.6f,
        0.5f, 0.2f, 0.6f
    };
    sRenderer.sShader = sCreateShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    svDrawTriangle(&sRenderer.triangle, vertices, color);
}

void vRenderFunc()
{
    glClearColor(0.0f, 0.45f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vUseShader(sRenderer.sShader);
    glBindVertexArray(sRenderer.triangle.m_uVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void vRenderTerminate()
{
    vDestroyShader(sRenderer.sShader);
}