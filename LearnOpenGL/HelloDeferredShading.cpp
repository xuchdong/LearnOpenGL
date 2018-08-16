//
//  HelloDeferredShading.cpp
//  LearnOpenGL
//
//  Created by xuchdong on 2018/8/14.
//  Copyright © 2018年 com.xuchdong. All rights reserved.
//

#include <stdio.h>
#include "LearnOpenGL.h"

#ifdef HELLO_DEFERREDSHADING

#include <string>
#include <vector>

#include "utils.hpp"
#include "shader_m.h"
#include "model.h"

using namespace std;

Shader *shaderGeometryPass, *shaderLightingPass, *shaderLightBox;

Model *cyborg;
vector<glm::vec3> objectPositions;

vector<glm::vec3> lightPositions;
vector<glm::vec3> lightColors;

void init(GLFWwindow* window)
{
    glEnable(GL_DEPTH_TEST);

    shaderGeometryPass = new Shader("g_buffer.vs", "g_buffer.fs");
    shaderLightingPass = new Shader("deferred_shading.vs", "deferred_shading.fs");
    shaderLightBox = new Shader("deferred_light_box.vs", "deferred_light_box.fs");

    shaderLightingPass->use();
    shaderLightingPass->setInt("gPosition", 0);
    shaderLightingPass->setInt("gNormal", 1);
    shaderLightingPass->setInt("gAlbedoSpec", 2);

    cyborg = new Model(srcBasepath + "nanosuit/nanosuit.obj");

    objectPositions.push_back(glm::vec3(-3.0, -3.0, -3.0));
    objectPositions.push_back(glm::vec3(0.0, -3.0, -3.0));
    objectPositions.push_back(glm::vec3(3.0, -3.0, -3.0));
    objectPositions.push_back(glm::vec3(-3.0, -3.0, 0.0));
    objectPositions.push_back(glm::vec3(0.0, -3.0, 0.0));
    objectPositions.push_back(glm::vec3(3.0, -3.0, 0.0));
    objectPositions.push_back(glm::vec3(-3.0, -3.0, 3.0));
    objectPositions.push_back(glm::vec3(0.0, -3.0, 3.0));
    objectPositions.push_back(glm::vec3(3.0, -3.0, 3.0));

    unsigned int NR_LIGHTS = 32;
    srand(13);
    for(unsigned int i = 0; i < NR_LIGHTS; i++)
    {
        float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
        float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        lightPositions.push_back(glm::vec3(xPos, yPos, zPos));

        float rColor = ((rand() % 100) / 200.0) + 0.5;
        float gColor = ((rand() % 100) / 200.0) + 0.5;
        float bColor = ((rand() % 100) / 200.0) + 0.5;
        lightColors.push_back(glm::vec3(rColor, gColor, bColor));
    }

}


void draw()
{
}


void clean()
{
}

#endif
