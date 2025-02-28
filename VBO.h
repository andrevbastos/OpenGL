#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
public:
	GLuint _id;
	VBO(GLsizeiptr size, GLfloat* vertices);
	void bind();
	void unbind();
	void bufferData(size_t size, const void* data);
	void destroy();
};

#endif