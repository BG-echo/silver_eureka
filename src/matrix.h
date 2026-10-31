#pragma once

#include "fixmatrix.h"
#include "math.h"

#define DEG2RAD(x) (double)(x * acos(-1.0f) / 180)

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

extern float* v3NormalizeVector(vec3 v);
extern float* v3CrossProduct(vec3 v1, vec3 v2);

extern mf16 mf16IdentityMatirx();
extern mf16 mf16TranslateMatrix(mf16 m, vec3 v);
extern mf16 mf16RotateMatrix(mf16 m, float ang, vec3 v);
extern mf16 mf16MakeFrustum(float fovY, float aspectRatio, float front, float back);
extern mf16 mf16LookAt(vec3 eye, vec3 centre, vec3 up);

extern float* fvValuePtr(mf16* m);
