#include "shader.h"
#include "stdio.h"
#include "stdlib.h"

#include "glew.h"
#include "glfw3.h"
#include "defines.h"

struct sShader
{
    unsigned int m_uShaderProgram;
    unsigned int m_uVertexShader, m_uFragmentShader;
};

static void svReadFile(char** buffer, const char* filepath)
{
    FILE* ioFile = fopen(filepath, "rb");
    ASSERT(!ioFile, fclose(ioFile), "Error! Couldn't open the file at: %s\n", filepath);

    int length = 0;
    while(fgetc(ioFile) != EOF)
    {
        ++length;
    }
    rewind(ioFile);

    *buffer = (char*)malloc((length + 1) * sizeof(char));
    for(int i = 0; !feof(ioFile); ++i)
    {
        *(*(buffer) + i) = fgetc(ioFile);
    }
    *(*(buffer) + length) = '\0';

    fclose(ioFile);
}

Shader* sCreateShader(const char* vertexPath, const char* fragmentPath)
{
    int success;
    char infoLog[512];
    char* strContent;

    Shader* shader = (Shader*)malloc(1 * sizeof(Shader));
    shader->m_uShaderProgram = glCreateProgram();

    //Vertex Shader
    svReadFile(&strContent, vertexPath);
    shader->m_uVertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(shader->m_uVertexShader, 1, (const char* const*)&strContent, NULL);
    glCompileShader(shader->m_uVertexShader);
    glGetShaderiv(shader->m_uVertexShader, GL_COMPILE_STATUS, &success);
    ASSERT(!success, glGetShaderInfoLog(shader->m_uVertexShader, 512, NULL, infoLog); glfwTerminate(), "ERROR::SHADER::VERTEX::COMPILATION_FAILED::%s\n", infoLog);

    //Fragment Shader
    svReadFile(&strContent, fragmentPath);
    shader->m_uFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader->m_uFragmentShader, 1, (const char* const*)&strContent, NULL);
    glCompileShader(shader->m_uFragmentShader);
    glGetShaderiv(shader->m_uFragmentShader, GL_COMPILE_STATUS, &success);
    ASSERT(!success, glGetShaderInfoLog(shader->m_uFragmentShader, 512, NULL, infoLog); glfwTerminate(), "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED::%s\n", infoLog);
    
    free(strContent);

    //Shader Program
    glAttachShader(shader->m_uShaderProgram, shader->m_uVertexShader);
    glAttachShader(shader->m_uShaderProgram, shader->m_uFragmentShader);

    glLinkProgram(shader->m_uShaderProgram);
    glGetShaderiv(shader->m_uShaderProgram, GL_LINK_STATUS, &success);
    ASSERT(!success, glGetShaderInfoLog(shader->m_uShaderProgram, 512, NULL, infoLog); glfwTerminate(), "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED::%s\n", infoLog);

    glDeleteShader(shader->m_uVertexShader);
    glDeleteShader(shader->m_uFragmentShader);

    return shader;
}

void vDestroyShader(Shader* const shader)
{
    free(shader);
}

void vUseShader(Shader* shader)
{
    glUseProgram(shader->m_uShaderProgram);
}

void vShaderSetInt(Shader* shader, const char* name, int value)
{
    glUniform1i(glGetUniformLocation(shader->m_uShaderProgram, name), value);
}