#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

void multiplyMatrixVector(float matrix[3][3], float& x, float& y);

class VBO {
public:
    VBO() {
        glGenBuffers(1, &_id);
    }

    GLuint id() {
        return _id;
    }

    void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }

    void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void bufferData(size_t size, const void* data) {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }

    void destroy() {
        glDeleteBuffers(1, &_id);
    }

private:
    GLuint _id;
};

class VAO {
public:
    VAO() {
        glGenBuffers(1, &_id);
    }

    GLuint id() {
        return _id;
    }

    void linkAttrib(VBO vbo, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr size, void* offset) {
        vbo.bind();
        glVertexAttribPointer(0, layout, numComponent, type, size, offset);
        glEnableVertexAttribArray(0);
    }

    void bind() {
        glBindVertexArray(_id);
    }

    void unbind() {
        glBindVertexArray(0);
    }

    void destroy() {
        glDeleteVertexArrays(1, &_id);
    }

private:
    GLuint _id;
};

class EBO {
public:
    EBO() {
        glGenBuffers(1, &_id);
    }

    GLuint id() {
        return _id;
    }

    void bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }

    void unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void bufferData(size_t size, const void* data) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void destroy() {
        glDeleteBuffers(1, &_id);
    }

private:
    GLuint _id;
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "OpenGL Rotation", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 500, 500);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    VBO vbo;
    VAO vao;
    EBO ebo;

    vao.bind();

    vbo.bind();
    vbo.bufferData(sizeof(vertices), vertices);

    ebo.bind();
    ebo.bufferData(sizeof(indices), indices);

    vao.linkAttrib(vbo, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    vbo.unbind();
    vao.unbind();
    ebo.unbind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        vao.bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void multiplyMatrixVector(float matrix[3][3], float& x, float& y) {
    float newX = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * 1;
    float newY = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * 1;
    x = newX;
    y = newY;
}