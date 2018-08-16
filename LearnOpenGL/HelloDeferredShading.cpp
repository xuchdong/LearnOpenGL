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

#include "utils.hpp"
#include "shader_m.h"
#include "model.h"

using namespace std;

Shader *shaderGeometryPass, *shaderLightingPass, *shaderLightBox;
Model *cyborg;

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
}


void draw()
{
}


void clean()
{
}

#endif
