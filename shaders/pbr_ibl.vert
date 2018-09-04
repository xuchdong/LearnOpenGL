#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoords;
out vec3 WordPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = aTexCoords;
    WordPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(model) * aNormal;

    gl_Position = projection * view * vec4(WordPos, 1.0);
}
