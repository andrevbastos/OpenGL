#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
uniform mat3 tSpin;
uniform mat3 tScale;
uniform mat3 tTranslation;
out vec3 color;
void main()
{
	color = aColor;
	vec3 pos = tTranslation * tSpin * tScale * vec3(aPos.xy, 1.0f);
	gl_Position = vec4(pos, 1.0);
}