#include "shapes.h"

#include "glew.h"
#include "glfw3.h"

#include "stdbool.h"
#include "stb_image.h"
#include "defines.h"

static void svAllocGraphicObjects(struct sGraphicObjects** g, size_t vsize, float* vertices, float* color, size_t tsize, float* texcoords, const char* texPath)
{
    (*g) = (struct sGraphicObjects*)malloc(1 * sizeof(struct sGraphicObjects));
    glGenVertexArrays(1, &(*g)->m_uVAO);
    glGenBuffers(3, (*g)->m_uVBO);
    
    glBindVertexArray((*g)->m_uVAO);
    
    //Vertices
    glBindBuffer(GL_ARRAY_BUFFER, (*g)->m_uVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(float), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Color
    glBindBuffer(GL_ARRAY_BUFFER, (*g)->m_uVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(float), color, GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    //Texture
    if(texPath != NULL)
    {
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
        GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
        
        glBindBuffer(GL_ARRAY_BUFFER, (*g)->m_uVBO[2]);
        glBufferData(GL_ARRAY_BUFFER, tsize * sizeof(float), texcoords, GL_STATIC_DRAW);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glBindVertexArray(0);
}

void vCreateObject(Object** t, size_t vsize, float* vertices, float* color, size_t tsize, float* texcoords, const char* texPath)
{
    (*t) = (Object*)malloc(1 * sizeof(Object));
    (*t)->m_fVertices = vertices;
    (*t)->m_fColor = color;

    svAllocGraphicObjects(&((*t)->GObject), vsize, (*t)->m_fVertices, (*t)->m_fColor, tsize, texcoords, texPath);
}

void vDestroyObject(Object* const t)
{
    glDeleteTextures(1, &t->GObject->m_texture);
    glDeleteBuffers(3, t->GObject->m_uVBO);
    glDeleteVertexArrays(1, &t->GObject->m_uVAO);
    free(t->GObject);
    free(t);
}