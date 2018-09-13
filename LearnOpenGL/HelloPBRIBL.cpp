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
#include "stb_image.h"

#define SRC_WIDTH   800
#define SRC_HEIGHT  600
string srcBasepath = "/Users/xuchdong/xuchdong/LearnOpenGL/src/";

GLFWwindow* mainWin;
Shader* pbrShader;
Shader* cubemapShader;
Shader* backgroundShader;

vector<glm::vec3> lightPositions;
vector<glm::vec3> lightColors;

unsigned int captureFBO, captureRBO;
unsigned int hdrTexture;

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

    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float *data = stbi_loadf((srcBasepath + "newport_loft.hdr").c_str(), &width, &height, &nrComponents, 0);
    unsigned int hdrTexture;
    if(data)
    {
        glGenTextures(1, &hdrTexture);
        glBindTexture(GL_TEXTURE_2D, hdrTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        cout << "Failed to load HDR image." << endl;
    }
}

void draw()
{

}

void clean()
{

}
#endif
