#version 330 core
layout (location = 0) in vec4 componentPosition;

uniform vec4 componentColor;
uniform mat4 projection_mx;
uniform mat4 view_mx = mat4(1.0f);
uniform mat4 model_mx = mat4(1.0f);

out vec4 pos;
void main()
{
	gl_Position = model_mx * projection_mx * componentPosition;
	pos = componentPosition;
}