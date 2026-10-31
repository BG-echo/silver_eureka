#include "matrix.h"

#include <stdio.h>
#include <math.h>

float* v3NormalizeVector(vec3 v)
{
    float length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if(length == 0.0f)
        return NULL;

    v[0] = v[0]/length;
    v[1] = v[1]/length;
    v[2] = v[2]/length;

    return v;
}

float* v3CrossProduct(vec3 v1, vec3 v2)
{
    static vec3 r;
    r[0] = v1[1] * v2[2] - v1[2] * v2[1];
    r[1] = v1[2] * v2[0] - v1[0] * v2[2];
    r[2] = v1[0] * v2[1] - v1[1] * v2[0];

    return r;
}

mf16 mf16IdentityMatirx()
{
    return (mf16){
        4, 4, 0,
        {
            [0][0] = fix16_from_float(1.0f),
            [1][1] = fix16_from_float(1.0f),
            [2][2] = fix16_from_float(1.0f),
            [3][3] = fix16_from_float(1.0f)
        }
    };
}

mf16 mf16TranslateMatrix(mf16 m, vec3 v)
{
    m.data[0][3] = fix16_from_float(v[0]);
    m.data[1][3] = fix16_from_float(v[1]);
    m.data[2][3] = fix16_from_float(v[2]);

    return m;
}

mf16 mf16RotateMatrix(mf16 m, float ang, vec3 v)
{
    if(!(v = v3NormalizeVector(v)))
        return m;

    float x = v[0];
    float y = v[1];
    float z = v[2];
    float radians = (float)DEG2RAD(ang);
    float c = cosf(radians);
    float s = sinf(radians);
    float oneMinusC = 1.0f - c;

    m.data[0][0] = fix16_from_float(c + x * x * oneMinusC);
    m.data[0][1] = fix16_from_float(x * y * oneMinusC - z * s);
    m.data[0][2] = fix16_from_float(x * z * oneMinusC + y * s);

    m.data[1][0] = fix16_from_float(x * y * oneMinusC + z * s);
    m.data[1][1] = fix16_from_float(c + y * y * oneMinusC);
    m.data[1][2] = fix16_from_float(y * z * oneMinusC - x * s);

    m.data[2][0] = fix16_from_float(x * z * oneMinusC - y * s);
    m.data[2][1] = fix16_from_float(y * z * oneMinusC + x * s);
    m.data[2][2] = fix16_from_float(c + z * z * oneMinusC);

    return m;
}

mf16 mf16MakeFrustum(float fovY, float aspectRatio, float front, float back)
{
    float tangent = tan(DEG2RAD(fovY/2));
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

mf16 mf16LookAt(vec3 eye, vec3 centre, vec3 up)
{
    static mf16 r;
    r = 
    {
        4, 4, 0,
        {
            
        }
    };
}

float* fvValuePtr(mf16* m)
{
    static float fdata[16];
    for(int i = 0, k = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j, ++k)
        {
            fdata[k] = fix16_to_float(m->data[i][j]);
#ifdef DBG
            printf("%f,", fdata[k]);
#endif
        }
#ifdef DBG
        putchar('\n');
#endif
    }

    return fdata;
}