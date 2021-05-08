#version 330 core
out vec4 FragColor;

uniform vec4 componentColor;
uniform mat4 entityPosition;

void main()
{
	FragColor = componentColor;
}