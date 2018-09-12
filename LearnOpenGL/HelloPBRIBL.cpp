//
//  HelloPBRIBL.cpp
//  LearnOpenGL
//
//  Created by xuchdong on 2018/9/4.
//  Copyright © 2018年 com.xuchdong. All rights reserved.
//

#include <stdio.h>
#include "LearnOpenGL.h"
#ifdef HELLO_PBR_IBL
#include <vector>
#include "shader_m.h"

#define SRC_WIDTH   800
#define SRC_HEIGHT  600

GLFWwindow* mainWin;
Shader* pbrShader;
Shader* cubemapShader;
Shader* backgroundShader;

vector<glm::vec3> lightPositions;
vector<glm::vec3> lightColors;

void init(GLFWwindow* window)
{
    mainWin = window;
    pbrShader = new Shader("pbr_ibl.vert", "pbr_ibl.frag");
    cubemapShader = new Shader("pbr_ibl_cubemap.vert", "pbr_ibl_cubemap.frag");
    backgroundShader = new Shader("pbr_ibl_background.vert", "pbr_ibl_background.frag");

    pbrShader->use();
    pbrShader->setVec3("albedo", 0.5f, 0.0f, 0.0f);
    pbrShader->setFloat("ao", 1.0f);

    backgroundShader->use();
    backgroundShader->setInt("environmentMap", 0);

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
