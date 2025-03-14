#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const unsigned int width = 500;
const unsigned int height = 500;

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

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, width, height);

    Shader shaderProgram("default.vert", "default.frag");

    VAO vao;
    vao.bind();

    VBO vbo(sizeof(vertices), vertices);
    EBO ebo(sizeof(indices), indices);

    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

	float time = 0.0f;
	glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.activate();

		glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

		time += 1 / 600.0f;
		model = glm::rotate(model, time, glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.4f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(width/height), 0.1f, 100.0f);

        GLuint modelLoc = glGetUniformLocation(shaderProgram._id, "model");
        GLuint viewLoc = glGetUniformLocation(shaderProgram._id, "view");
        GLuint projLoc = glGetUniformLocation(shaderProgram._id, "proj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

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