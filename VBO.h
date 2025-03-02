#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
    GLuint _id;
    VBO(GLsizeiptr size, const void* vertices);

    void bind();
    void unbind();
    void destroy();
};

#endif