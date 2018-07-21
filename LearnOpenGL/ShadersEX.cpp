//
//  ShadersEX.cpp
//  LearnOpenGL
//
//  Created by xuchdong on 2018/7/21.
//  Copyright © 2018年 com.xuchdong. All rights reserved.
//

#include <stdio.h>
#include "LearnOpenGL.h"
#include "Shader.h"

#ifdef SHADERSEX

Shader *shader;
unsigned int VAO, VBO;

void init()
{
    shader = new Shader("shaders.vs", "shaders.fs");
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] = {
        0.5f,   -0.5f,  0.0f,   1.0f,   0.0f,   0.0f,
        -0.5f,  -0.5f,  0.0f,   0.0f,   1.0f,   0.0f,
        0.0f,   0.5f,   0.0f,   0.0f,   0.0f,   1.0f
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void draw()
{
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void clean()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
#endif
