//
//  HelloColors.cpp
//  LearnOpenGL
//
//  Created by xuchdong on 2018/7/25.
//  Copyright © 2018年 com.xuchdong. All rights reserved.
//

#include <stdio.h>
#include "LearnOpenGL.h"

#ifdef HELLO_COLOR
#include <string>
#include <iostream>
#include "shader_m.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = SRC_WIDTH / 2.0f;
float lastY = SRC_HEIGHT / 2.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Shader *lightShader;
Shader *objShader;

unsigned int lightVAO, objVAO, VBO;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void init(GLFWwindow* window)
{
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };


    lightShader = new Shader("hello_colors_light.vs", "hello_colors_light.fs");
    objShader = new Shader("hello_colors_obj.vs", "hello_colors_obj.fs");

    glGenVertexArrays(1, &objVAO);
    glBindVertexArray(objVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
}

void draw()
{
    glClear(GL_DEPTH_BUFFER_BIT);

    objShader->use();
    objShader->setVec3("objColor", 1.0f, 0.5f, 0.31f);
    objShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SRC_WIDTH / SRC_HEIGHT , 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 model;

    model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    objShader->setMat4("model", model);
    objShader->setMat4("view", view);
    objShader->setMat4("projection", projection);
    glBindVertexArray(objVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    lightShader->use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    lightShader->setMat4("model", model);
    lightShader->setMat4("view", view);
    lightShader->setMat4("projection", projection);
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void clean()
{
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteVertexArrays(1, &objVAO);
    glDeleteBuffers(1, &VBO);
}
#endif
