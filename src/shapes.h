#pragma once

struct sGraphicObjects
{
    unsigned int m_uVAO;
    unsigned int m_uVBO[3];
    unsigned int m_texture;
};

typedef struct sTriangle 
{
    float* m_fVertices;
    float* m_fColor;

    struct sGraphicObjects* GObject;
}Triangle;

typedef struct sContainer
{
    float* m_fVertices;
    float* m_fColor;

    struct sGraphicObjects* GObject;
}Container;


extern void vCreateTriangle(Triangle** t, float* vertices, float* color, const char* texPath);
extern void vCreateContainer(Container** c, float* vertices, float* color, const char* texPath);

extern void vDestroyTriangle(Triangle* const t);
extern void vDestroyContainer(Container* const c);