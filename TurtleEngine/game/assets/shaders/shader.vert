#version 330 core
layout (location = 0) in vec4 initial_coordinates;
layout (location = 1) in vec2 textureCoord;

uniform mat4 model_mx;
uniform vec2 size_vec2;
uniform mat4 projection_mx;
uniform vec4 component_color_vec4;

out vec2 texCoordinate;
void main()
{
	texCoordinate = textureCoord;

	vec4 transform = initial_coordinates;
	transform.x *= size_vec2.x;
	transform.y *= size_vec2.y;

	gl_Position = model_mx * projection_mx * transform;
}