//
//  HelloBloom.cpp
//  LearnOpenGL
//
//  Created by xuchdong on 2018/8/13.
//  Copyright © 2018年 com.xuchdong. All rights reserved.
//

#include <stdio.h>
#include "LearnOpenGL.h"

#ifdef HELLO_BLOOM

#include <vector>

#include "shader_m.h"
#include "utils.hpp"

using namespace std;

Shader *shader, *shaderLight, *shaderBlur, *shaderBloomFinal;
unsigned int woodTexture, containerTexture;

unsigned int hdrFBO;
unsigned int colorBuffers[2];
unsigned int rboDepth;

unsigned int pingpongFBO[2];
unsigned int pingpongColorbuffers[2];

vector<glm::vec3> lightPositions;
vector<glm::vec3> lightColors;

void init(GLFWwindow* window)
{
    glEnable(GL_DEPTH_TEST);

    shader = new Shader("bloom.vs", "bloom.fs");
    shaderLight = new Shader("bloom.vs", "light_box.fs");
    shaderBlur = new Shader("blur.vs", "blur.fs");
    shaderBloomFinal = new Shader("bloom_final.vs", "bloom_final.fs");

    woodTexture = loadTexture("wood.png", true);
    containerTexture = loadTexture("container2.png", true);

    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

    glGenTextures(2, colorBuffers);
    for(unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SRC_WIDTH, SRC_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // attach texture to framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }

    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SRC_WIDTH, SRC_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    unsigned int attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, attachments);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        cout << "Framebuffer not complete!" << endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorbuffers);
    for(unsigned int i = 0; i < 2; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SRC_WIDTH, SRC_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            cout << "Framebuffer not complete!" << endl;
        }
    }

    lightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f));
    lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
    lightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
    lightPositions.push_back(glm::vec3(-0.8f, 2.4f, -1.0f));

    lightColors.push_back(glm::vec3(2.0f, 2.0f, 2.0f));
    lightColors.push_back(glm::vec3(1.5f, 0.0f, 0.0f));
    lightColors.push_back(glm::vec3(0.0f, 0.0f, 1.5f));
    lightColors.push_back(glm::vec3(0.0f, 1.5f, 0.0f));

    shader->use();
    shader->setInt("diffuseTexture", 0);
    shaderBlur->use();
    shaderBlur->setInt("image", 0);
    shaderBloomFinal->use();
    shaderBloomFinal->setInt("scene", 0);
    shaderBloomFinal->setInt("bloomBlur", 1);
}

void draw()
{
}

void clean()
{
}

#endif
