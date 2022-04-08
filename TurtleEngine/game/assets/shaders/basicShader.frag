#version 330 core

out vec4 FragColor;

uniform vec4 component_color_vec4;

in vec2 texCoordinate;

void main()
{
	FragColor = component_color_vec4;
}