#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include "ShaderTypes.h"

class ShaderProgram
{
public:
	GLuint ProgramId;

	ShaderProgram();
	~ShaderProgram();
	void AttachShader(ShaderTypes shaderType, std::string shaderPath);
	void LinkProgram();
	void UseProgram();
	void DeleteProgram();


private:
	std::vector<GLuint> Shaders;
};
