//
//  HelloPBRLighting.cpp
//  LearnOpenGL
//
//  Created by xuchdong on 2018/9/2.
//  Copyright © 2018年 com.xuchdong. All rights reserved.
//

#include <stdio.h>

#include "LearnOpenGL.h"

#ifdef HELLO_PBRLIGHTING

#include <vector>

#include "shader_m.h"
#include "camera.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

Shader *shader;

vector<glm::vec3> lightPositions;
vector<glm::vec3> lightColors;

void init(GLFWwindow* window)
{
    shader = new Shader("pbr.vert", "pbr.frag");
    shader->use();
    shader->setVec3("albedo", 0.5f, 0.0f, 0.0f);
    shader->setFloat("ao", 1.0f);

    lightPositions.push_back(glm::vec3(-10.0f,  10.0f, 10.0f));
    lightPositions.push_back(glm::vec3( 10.0f,  10.0f, 10.0f));
    lightPositions.push_back(glm::vec3(-10.0f, -10.0f, 10.0f));
    lightPositions.push_back(glm::vec3( 10.0f, -10.0f, 10.0f));

    lightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
    lightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
    lightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
    lightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));
}

void draw()
{

}

void clean()
{

}

#endif
