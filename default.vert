#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 xRotation;
uniform mat4 yRotation;
uniform mat4 zRotation;
out vec3 color;
void main()
{
	color = aColor;
	vec4 pos = zRotation * yRotation * xRotation * vec4(aPos, 1.0f);
	gl_Position = vec4(pos);
}