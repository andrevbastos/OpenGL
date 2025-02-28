#include"VAO.h" 

VAO::VAO() {
    glGenBuffers(1, &_id);
}

GLuint VAO::id() {
    return _id;
}

void VAO::linkAttrib(VBO vbo, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void* offset) {
    vbo.bind();
    glVertexAttribPointer(layout, numComponent, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}


void VAO::bind() {
    glBindVertexArray(_id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::destroy() {
    glDeleteVertexArrays(1, &_id);
}