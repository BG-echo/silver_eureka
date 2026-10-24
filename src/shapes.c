#include "shapes.h"

#include "glew.h"
#include "glfw3.h"

#include "stdbool.h"
#include "stb_image.h"
#include "defines.h"

static void svAllocGraphicObjects(struct sGraphicObjects** g, size_t size, float* vertices, float* color, const char* texPath)
{
    (*g) = (struct sGraphicObjects*)malloc(1 * sizeof(struct sGraphicObjects));
    glGenBuffers(1, &(*g)->m_uVAO);
    glGenBuffers(3, (*g)->m_uVBO);
    
    glBindVertexArray((*g)->m_uVAO);
    
    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, (*g)->m_uVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Color
    glBindBuffer(GL_ARRAY_BUFFER, (*g)->m_uVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), color, GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //Texture
    if(texPath != NULL)
    {
        float texCoords[] = 
        {
            0.0f, 1.0f,  // top-right corner
            1.0f, 0.0f,  // lower-right corner
            0.0f, 0.0f,  // lower-left corner  
            0.0f, 0.0f,  // lower-left corner  
            1.0f, 1.0f,  // top-left corner
            0.0f, 1.0f,  // top-right corner
        };
        
        glGenTextures(1, &(*g)->m_texture);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (*g)->m_texture);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load_thread(true);
        unsigned char* data = stbi_load(texPath, &width, &height, &nrChannels, 0);
        ASSERT(!data, glfwTerminate(),"Error couldn't load the specified texture at: %s", texPath);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
        
        glBindBuffer(GL_ARRAY_BUFFER, (*g)->m_uVBO[2]);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), texCoords, GL_STATIC_DRAW);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(0);
}

void vCreateTriangle(Triangle** t, float* vertices, float* color, const char* texPath)
{
    (*t) = (Triangle*)malloc(1 * sizeof(Triangle));
    (*t)->m_fVertices = vertices;
    (*t)->m_fColor = color;

    svAllocGraphicObjects(&((*t)->GObject), 9, (*t)->m_fVertices, (*t)->m_fColor, texPath);
}

void vCreateContainer(Container** c, float* vertices, float* color, const char* texPath)
{
    (*c) = (Container*)malloc(1 * sizeof(Container));
    (*c)->m_fVertices = vertices;
    (*c)->m_fColor = color;
    
    svAllocGraphicObjects(&((*c)->GObject), 18, (*c)->m_fVertices, (*c)->m_fColor, texPath);
}

void vDestroyTriangle(Triangle* const t)
{
    free(t->GObject);
    free(t);
}

void vDestroyContainer(Container* const c)
{
    free(c->GObject);
    free(c);
}