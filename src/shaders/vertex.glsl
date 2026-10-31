#version 330 core

layout (location = 0) in vec3 vertices;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    outColor = color;
    gl_Position = projection * view * model * vec4(vertices, 1.0);
    TexCoord = aTexCoord;
}
