#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

float cx = 0.0f;
float cy = 0.0f;
float l = 0.2f;

float vertices[] = {
	// positions  // colors
    cx +l, cy +l, 1.0f, 0.0f, 0.0f,
    cx +l, cy -l, 0.5f, 0.0f, 1.0f,
	cx -l, cy -l, 1.0f, 0.0f, 0.0f,
	cx -l, cy +l, 0.5f, 0.0f, 1.0f
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};

float tSpin[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

float tScale[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

float tTranslation[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f
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

    vao.linkAttrib(vbo, 0, 2, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 5 * sizeof(float), (void*)(2 * sizeof(float)));

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    GLuint spinLoc = glGetUniformLocation(shaderProgram._id, "tSpin");
    GLuint scaleLoc = glGetUniformLocation(shaderProgram._id, "tScale");
    GLuint translationLoc = glGetUniformLocation(shaderProgram._id, "tTranslation");

    float t = 0.0f;

    float sx = 1.0f;
    float sy = 1.0f;
    float magS = 1.0f;

    float tx = 0.0f;

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.activate();

        t += 1 / 600.0f;
        tSpin[0] = cos(t);
        tSpin[1] = -sin(t);
        tSpin[3] = sin(t);
        tSpin[4] = cos(t);

        if (sx > 3.0f || sx < 1.0f) {
            magS *= -1;
        }

        sx += 1 / 600.0f * magS;
        sy += 1 / 600.0f * magS;
        tScale[0] = sx;
        tScale[4] = sy;

        tTranslation[6] = (1.0f - (sqrt(2) * l)) * sin(t);

        glUniformMatrix3fv(spinLoc, 1, GL_FALSE, tSpin);
        glUniformMatrix3fv(scaleLoc, 1, GL_FALSE, tScale);
        glUniformMatrix3fv(translationLoc, 1, GL_FALSE, tTranslation);

        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shaderProgram.destroy();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}