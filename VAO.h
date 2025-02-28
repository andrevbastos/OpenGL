#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
    VAO();
    GLuint id();
    void linkAttrib(VBO vbo, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void* offset);
    void bind();
    void unbind();
    void destroy();
private:
    GLuint _id;
};

#endif
