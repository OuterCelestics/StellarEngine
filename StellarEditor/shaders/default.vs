#version 460 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
//layout (location = 1) in vec3 aTextCoord;
layout (location = 1) in vec3 aTextCoord;

//out vec3 ourColor;
out vec2 TextCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TextCoord = vec2(aTextCoord.x, aTextCoord.y);
}