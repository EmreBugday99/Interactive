#pragma once

#include <map>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace TurtleEngine
{
	class ShaderManager
	{
	public:
		static std::map<std::string, GLuint> ShaderCache;
		static std::map<std::string, GLint> ShaderUniformCache;

		static GLuint CreateShader(bool& successful, std::string shaderName, std::string vertexSourcePath, std::string fragmentSourcePath);
		static void SetUniformData(GLuint& programId, std::string uniformName, GLint& value);
		static void SetUniformData(GLuint& programId, std::string uniformName, GLfloat& value);
		static void SetUniformData(GLuint& programId, std::string uniformName, glm::vec2& value);
		static void SetUniformData(GLuint& programId, std::string uniformName, glm::vec3& value);
		static void SetUniformData(GLuint& programId, std::string uniformName, glm::vec4& value);
		static void SetUniformData(GLuint& programId, std::string uniformName, glm::mat4& value);
	private:
		static void CheckShaderCompilationResult(const GLuint& shader, bool& successful);
		static GLint GetUniformLocation(std::string uniformName, GLuint programId);
	};
}
