#version 330 core

out vec4 FragColor;

uniform vec4 componentColor;
uniform mat4 entityPosition;
uniform float light_distance;

in vec2 texCoordinate;

void main()
{
	FragColor = componentColor;
}