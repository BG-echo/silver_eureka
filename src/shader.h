#pragma once

typedef struct sShader Shader;

extern Shader* sCreateShader(const char* vertexPath, const char* fragmentPath);
extern void vDestroyShader(Shader* const shader);
extern void vUseShader(Shader* shader);
extern void vShaderSetInt(Shader* shader, const char* name, int value);