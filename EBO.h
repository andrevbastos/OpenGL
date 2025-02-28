#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
public:
	GLuint _id;
	EBO(GLsizeiptr size, GLuint* indices);
	void bind();
	void unbind();
	void bufferData(size_t size, const void* data);
	void destroy();
};

#endif