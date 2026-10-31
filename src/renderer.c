#include "glew.h"
#include "glfw3.h"

#include "stdio.h"
#include "stdlib.h"

#include "renderer.h"
#include "shader.h"
#include "shapes.h"

#include "matrix.h"
#include "data.h"

struct 
{
    Shader* sShader;
    Object* object;
    
    mf16 view;
    mf16 projection;
    mf16 model;
}sRenderer;

void vRenderInit()
{
    glEnable(GL_DEPTH_TEST);

    sRenderer.sShader = sCreateShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    vCreateObject(&sRenderer.object, 108, vertices, color, 72, texcoords, "../bin/textures/wall.jpg");

    vUseShader(sRenderer.sShader);
    vShaderSetInt(sRenderer.sShader, "tex", 0);

    sRenderer.view = mf16IdentityMatirx();
    sRenderer.view = mf16TranslateMatrix(sRenderer.view, (vec3){0.0f, 0.0f, -3.0f});
    vShaderSetMatrix(sRenderer.sShader, "view", fvValuePtr(&sRenderer.view));

    sRenderer.projection = mf16MakeFrustum(45.0f, 800.0f / 800.0f, 0.1f, 100.0f);
    vShaderSetMatrix(sRenderer.sShader, "projection", fvValuePtr(&sRenderer.projection));
}

void vRenderFunc()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vUseShader(sRenderer.sShader);
    sRenderer.model = mf16IdentityMatirx();
    sRenderer.model = mf16RotateMatrix(sRenderer.model, (float)glfwGetTime() * 50.0f, (vec3){0.5f, 1.0f, 0.0f});
    vShaderSetMatrix(sRenderer.sShader, "model", fvValuePtr(&sRenderer.model));

    glBindVertexArray(sRenderer.object->GObject->m_uVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void vRenderTerminate()
{
    vDestroyObject(sRenderer.object);
    vDestroyShader(sRenderer.sShader);
}