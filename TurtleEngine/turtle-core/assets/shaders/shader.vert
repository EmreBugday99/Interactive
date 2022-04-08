#version 330 core
layout (location = 0) in vec4 componentPosition;
layout (location = 1) in vec2 textureCoord;

uniform vec4 componentColor;
uniform vec4 size;
uniform mat4 projection_mx;
uniform mat4 view_mx = mat4(1.0f);
uniform mat4 model_mx = mat4(1.0f);
uniform sampler2D texture0;

out vec4 pos;
out vec2 texCoordinate;
void main()
{
	gl_Position = model_mx * projection_mx * componentPosition * size;
	pos = componentPosition;
	texCoordinate = textureCoord;
}