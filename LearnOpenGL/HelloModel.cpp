//
//  HelloModel.cpp
//  LearnOpenGL
//
//  Created by xuchdong on 2018/7/29.
//  Copyright © 2018年 com.xuchdong. All rights reserved.
//

#include <stdio.h>
#include "LearnOpenGL.h"

#ifdef HELLO_MODEL

#include "shader_m.h"
#include "model.h"
#include "Camera.h"

string basePath = "/Users/xuchdong/xuchdong/LearnOpenGL/src/";
Shader *ourShader;
Model *ourModel;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SRC_WIDTH / 2.0f;
float lastY = SRC_HEIGHT / 2.0F;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

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

    glEnable(GL_DEPTH_TEST);
    ourShader = new Shader("hello_model.vs", "hello_model.fs");
    ourModel = new Model(basePath + "nanosuit/nanosuit.obj");
}

void draw()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    ourShader->use();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SRC_WIDTH/(float)SRC_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    ourShader->setMat4("projection", projection);
    ourShader->setMat4("view", view);
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    ourShader->setMat4("model", model);

    ourModel->Draw(*ourShader);
}

void clean()
{
    
}
#endif
