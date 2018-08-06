
//
//  LearnOpenGL.h
//  LearnOpenGL
//
//  Created by xuchdong on 2018/7/21.
//  Copyright © 2018年 com.xuchdong. All rights reserved.
//

#ifndef LearnOpenGL_h
#define LearnOpenGL_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define HELLO_SHADOWMAPPING

#define SRC_WIDTH   800
#define SRC_HEIGHT  600

extern void init(GLFWwindow* window);
extern void draw();
extern void clean();

#endif /* LearnOpenGL_h */
