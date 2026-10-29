#pragma once

#include <stddef.h>

struct sGraphicObjects
{
    unsigned int m_uVAO;
    unsigned int m_uVBO[3];
    unsigned int m_texture;
};

typedef struct sObject 
{
    float* m_fVertices;
    float* m_fColor;

    struct sGraphicObjects* GObject;
}Object;


extern void vCreateObject(Object** t, size_t vsize, float* vertices, float* color, size_t tsize, float* texcoords, const char* texPath);

extern void vDestroyObject(Object* const t);