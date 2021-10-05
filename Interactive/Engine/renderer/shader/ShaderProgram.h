#pragma once
#include <map>
#include <string>
#include <vector>
#include <glad/glad.h>
#include "ShaderTypes.h"
#include <glm/glm.hpp>

class ShaderProgram
{
public:
	GLuint ProgramId;

private:
	std::vector<GLuint> Shaders;
	std::map<std::string, GLint> ShaderUniformCache;

public:
	ShaderProgram();
	~ShaderProgram();

	void AttachShader(ShaderTypes shaderType, std::string shaderPath);
	void CreateShader();
	void LinkProgram();
	void UseProgram();
	void UnbindProgram();

	void SetUniformData(std::string uniformName, GLint& value);
	void SetUniformData(std::string uniformName, GLfloat& value);
	void SetUniformData(std::string uniformName, glm::vec2& value);
	void SetUniformData(std::string uniformName, glm::vec3& value);
	void SetUniformData(std::string uniformName, glm::vec4& value);
	void SetUniformData(std::string uniformName, glm::mat4& value);

	void DeleteProgram();

private:
	//TODO: Cache Uniform Locations
	GLint GetUniformLocation(std::string uniformName);
};
