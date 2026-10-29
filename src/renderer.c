#include "glew.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "renderer.h"
#include "shader.h"
#include "shapes.h"

#include "fixmatrix.h"

struct 
{
    Shader* sShader;
    Object* object;
}sRenderer;

static float* sfValuePtr(mf16* m)
{
    static float fdata[16];
    for(int i = 0, k = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j, ++k)
        {
            fdata[k] = fix16_to_float(m->data[i][j]);
            printf("%f,", fdata[k]);
        }
        putchar('\n');
    }

    return fdata;
}

static mf16 smMakeFrustum(float fovY, float aspectRatio, float front, float back)
{
    const float DEG2RAD = acos(-1.0f) / 180;

    float tangent = tan(fovY/2 * DEG2RAD);
    float top = front * tangent;
    float right = top * aspectRatio;

    mf16 matrix = 
    {
        4, 4, 0,
        {
            [0][0] = fix16_from_float(front / right),
            [1][1] = fix16_from_float(front / top),
            [2][2] = fix16_from_float(-(back + front) / (back - front)),
            [3][2] = fix16_from_float(-1),
            [2][3] = fix16_from_float(-(2 * back * front) / (back - front)),
            [3][3] = fix16_from_float(0)
        }
    };

    return matrix;
}

void vRenderInit()
{
    glEnable(GL_DEPTH_TEST);

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

    float texcoords[12] =
    {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };

    sRenderer.sShader = sCreateShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    vCreateObject(&sRenderer.object, 18, vertices, color, 12, texcoords, "../bin/textures/wall.jpg");

    vUseShader(sRenderer.sShader);
    vShaderSetInt(sRenderer.sShader, "tex", 0);

    mf16 model = {
        4, 4, 0,
        {
            [0][0] = fix16_from_float(1.0f),
            [1][1] = fix16_from_float(1.0f),
            [2][2] = fix16_from_float(1.0f),
            [3][3] = fix16_from_float(1.0f)
        }
    };
    vShaderSetMatrix(sRenderer.sShader, "model", sfValuePtr(&model));

    mf16 view = {
        4, 4, 0,
        {
            [0][0] = fix16_from_float(1.0f),
            [1][1] = fix16_from_float(1.0f),
            [2][2] = fix16_from_float(1.0f),
            [2][3] = fix16_from_float(-3.0f),
            [3][3] = fix16_from_float(1.0f)
        }
    };
    vShaderSetMatrix(sRenderer.sShader, "view", sfValuePtr(&view));

    mf16 projection = smMakeFrustum(45.0f, 800.0f / 800.0f, 0.1f, 100.0f);
    vShaderSetMatrix(sRenderer.sShader, "projection", sfValuePtr(&projection));
}

void vRenderFunc()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vUseShader(sRenderer.sShader);
    glBindVertexArray(sRenderer.object->GObject->m_uVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void vRenderTerminate()
{
    vDestroyObject(sRenderer.object);
    vDestroyShader(sRenderer.sShader);
}