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

#include "shader_m.h"

Shader *shader;

void init(GLFWwindow* window)
{
    shader = new Shader("pbr.vert", "pbr.frag");
}

void draw()
{

}

void clean()
{

}

#endif
