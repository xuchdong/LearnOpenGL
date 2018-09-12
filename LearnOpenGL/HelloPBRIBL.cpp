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
#include "shader_m.h"

#define SRC_WIDTH   800
#define SRC_HEIGHT  600

GLFWwindow* mainWin;
Shader* pbrShader;
Shader* cubemapShader;
Shader* backgroundShader;

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
}

void draw()
{

}

void clean()
{

}
#endif
