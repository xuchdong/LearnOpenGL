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

#include <iostream>
#include <vector>

#include "shader_m.h"
#include "camera.h"

using namespace std;

void renderSphere();

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

Shader *shader;

vector<glm::vec3> lightPositions;
vector<glm::vec3> lightColors;

int nrRows    = 7;
int nrColumns = 7;
float spacing = 2.5;

void init(GLFWwindow* window)
{
    glEnable(GL_DEPTH_TEST);
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

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SRC_WIDTH / SRC_HEIGHT, 0.1f, 100.0f);
    shader->setMat4("projection", projection);
}

void draw()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    shader->use();
    glm::mat4 view = camera.GetViewMatrix();
    shader->setMat4("view", view);
    shader->setVec3("camPos", camera.Position);

    glm::mat4 model;
    for(int row = 0; row < nrRows; ++row)
    {
        shader->setFloat("metallic", (float) row / nrRows);
        for(int col = 0; col < nrColumns; ++col)
        {
            shader->setFloat("roughness", glm::clamp((float) col / nrColumns, 0.05f, 1.0f));
            model = glm::mat4();
            model = glm::translate(model, glm::vec3(
                (col - (nrColumns / 2)) * spacing,
                (row - (nrRows / 2)) * spacing,
                0.0f
            ));
            shader->setMat4("model", model);
            renderSphere();
        }
    }
}

unsigned int sphereVAO = 0;
unsigned int indexCount;
void renderSphere()
{
    if(sphereVAO == 0)
    {
        glGenVertexArrays(1, &sphereVAO);
        unsigned int vbo, ebo;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        vector<glm::vec3> positions;
        vector<glm::vec2> uv;
        vector<glm::vec3> normals;
        vector<unsigned int> indices;

        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for(unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for(unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                float xSegment = (float) x / (float)X_SEGMENTS;
                float ySegment = (float) y / (float)Y_SEGMENTS;
                float xPos = cos(xSegment * 2.0f * PI) * sin(ySegment * PI);
                float yPos = cos(ySegment * PI);
                float zPos = sin(xSegment * 2.0f * PI) * sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for(int y = 0; y < Y_SEGMENTS; ++y)
        {
            if(!oddRow)
            {
                for(int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y         * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1)   * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for(int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back(y         * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1)   * (X_SEGMENTS + 1) + x);
                }

            }
            oddRow = !oddRow;
        }
        indexCount = indices.size();

        vector<float> data;
        for(int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if(uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
            if(normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
        }
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        float stride = (3 + 2 + 3) * sizeof(float);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)(3 + sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void *)(5 + sizeof(float)));
    }
    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}


void clean()
{

}

#endif
