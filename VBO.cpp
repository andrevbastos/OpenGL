#include "VBO.h"

VBO::VBO(GLsizeiptr size, const void* vertices)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::destroy()
{
    glDeleteBuffers(1, &_id);
}