#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void rotate();

float cx = 0.0f;
float cy = 0.0f;
float cz = 0.0f;
float l = 0.2f;

float vertices[] = {
    // positions         // colors

    // front face
    cx + l, cy + l, cz + l, 0.0f, 0.0f, 1.0f,
    cx + l, cy - l, cz + l, 0.0f, 0.0f, 1.0f,
    cx - l, cy - l, cz + l, 0.0f, 0.0f, 1.0f,
    cx - l, cy + l, cz + l, 0.0f, 0.0f, 1.0f,

    // back face
    cx + l, cy + l, cz - l, 1.0f, 0.0f, 0.0f,
    cx + l, cy - l, cz - l, 1.0f, 0.0f, 0.0f,
    cx - l, cy - l, cz - l, 1.0f, 0.0f, 0.0f,
    cx - l, cy + l, cz - l, 1.0f, 0.0f, 0.0f,

    // left face
    cx - l, cy + l, cz + l, 0.0f, 1.0f, 0.0f,
    cx - l, cy - l, cz + l, 0.0f, 1.0f, 0.0f,
    cx - l, cy - l, cz - l, 0.0f, 1.0f, 0.0f,
    cx - l, cy + l, cz - l, 0.0f, 1.0f, 0.0f,

    // right face
    cx + l, cy + l, cz + l, 1.0f, 1.0f, 0.0f,
    cx + l, cy - l, cz + l, 1.0f, 1.0f, 0.0f,
    cx + l, cy - l, cz - l, 1.0f, 1.0f, 0.0f,
    cx + l, cy + l, cz - l, 1.0f, 1.0f, 0.0f,

    // top face
    cx + l, cy + l, cz + l, 0.0f, 1.0f, 1.0f,
    cx + l, cy + l, cz - l, 0.0f, 1.0f, 1.0f,
    cx - l, cy + l, cz - l, 0.0f, 1.0f, 1.0f,
    cx - l, cy + l, cz + l, 0.0f, 1.0f, 1.0f,

    // bottom face
    cx + l, cy - l, cz + l, 1.0f, 0.0f, 1.0f,
    cx + l, cy - l, cz - l, 1.0f, 0.0f, 1.0f,
    cx - l, cy - l, cz - l, 1.0f, 0.0f, 1.0f,
    cx - l, cy - l, cz + l, 1.0f, 0.0f, 1.0f
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3,

    4, 5, 7,
    5, 6, 7,

    8, 9, 11,
    9, 10, 11,

    12, 13, 15,
    13, 14, 15,

    16, 17, 19,
    17, 18, 19,

    20, 21, 23,
    21, 22, 23
};

float xAngle = 0.0f;
float xRotation[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float yAngle = 0.0f;
float yRotation[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float zAngle = 0.0f;
float zRotation[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 500, 500);

    Shader shaderProgram("default.vert", "default.frag");

    VAO vao;
    vao.bind();

    VBO vbo(sizeof(vertices), vertices);
    EBO ebo(sizeof(indices), indices);

    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    GLuint xRotLoc = glGetUniformLocation(shaderProgram._id, "xRotation");
    GLuint yRotLoc = glGetUniformLocation(shaderProgram._id, "yRotation");
    GLuint zRotLoc = glGetUniformLocation(shaderProgram._id, "zRotation");

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

	glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.activate();

        xAngle += 1 / 6000.0f;
        yAngle -= 1 / 6000.0f;
        zAngle += 1 / 6000.0f;
        rotate();

        glUniformMatrix4fv(xRotLoc, 1, GL_FALSE, xRotation);
        glUniformMatrix4fv(yRotLoc, 1, GL_FALSE, yRotation);
        glUniformMatrix4fv(zRotLoc, 1, GL_FALSE, zRotation);

        vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shaderProgram.destroy();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void rotate() {
    xRotation[5] = cos(xAngle);
    xRotation[6] = -sin(xAngle);
    xRotation[9] = sin(xAngle);
    xRotation[10] = cos(xAngle);

    yRotation[0] = cos(yAngle);
    yRotation[2] = sin(yAngle);
    yRotation[8] = -sin(yAngle);
    yRotation[10] = cos(yAngle);

    zRotation[0] = cos(zAngle);
    zRotation[1] = -sin(zAngle);
    zRotation[4] = sin(zAngle);
    zRotation[5] = cos(zAngle);
}