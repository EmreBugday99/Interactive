#include "ShaderManager.h"
#include <iostream>
#include <glm/ext.hpp>
#include "../file-io/DiskReader.h"

namespace TurtleEngine
{
	std::map<std::string, GLuint> ShaderManager::ShaderCache;
	std::map<std::string, GLint> ShaderManager::ShaderUniformCache;

	GLuint ShaderManager::CreateShader(bool& successful, std::string shaderName, std::string vertexSourcePath, std::string fragmentSourcePath)
	{
		successful = false;

		const auto cacheIterator = ShaderCache.find(shaderName);
		if (cacheIterator != ShaderCache.end())
		{
			successful = true;
			return ShaderCache[shaderName];
		}

		const GLuint programId = glCreateProgram();

		const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertexCode;
		DiskReader::ReadString(vertexCode, vertexSourcePath);
		const char* vertexSourceCode = vertexCode.c_str();

		std::string fragmentCode;
		DiskReader::ReadString(fragmentCode, fragmentSourcePath);
		const char* fragmentSourceCode = fragmentCode.c_str();

		// Setting the source code of the vertex shader
		glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
		// Compiling the source code of the vertex shader
		glCompileShader(vertexShader);

		// Checking for compilation errors inside the recently compiled vertex shader
		bool vertexCompiledSuccessfully = false;
		CheckShaderCompilationResult(vertexShader, vertexCompiledSuccessfully);
		// If the shader failed to compile; It is pointless to keep it in the GPU memory
		if (vertexCompiledSuccessfully == false)
			glDeleteShader(vertexShader);
		else
			glAttachShader(programId, vertexShader);

		// Setting the source code of the fragment shader
		glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);
		// Compiling the source code of the fragment shader
		glCompileShader(fragmentShader);
		// Checking for compilation errors inside the recently compiled fragment shader

		bool fragmentCompiledSuccessfully = false;
		CheckShaderCompilationResult(fragmentShader, fragmentCompiledSuccessfully);
		// If the fragment shader failed to compile, it is pointless to keep it in the GPU memory
		if (fragmentCompiledSuccessfully == false)
			glDeleteShader(fragmentShader);
		else
			glAttachShader(programId, fragmentShader);

		// If this program failed to compile successfully it should be deleted.
		if (vertexCompiledSuccessfully && fragmentCompiledSuccessfully)
		{
			successful = true;
			glLinkProgram(programId);
			glValidateProgram(programId);

			// We no longer need to keep individual shader as we have a working program
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			ShaderCache[shaderName] = programId;

			return programId;
		}

		glDeleteProgram(programId);
		return 0;
	}

	void ShaderManager::SetUniformData(GLuint& programId, std::string uniformName, GLint& value)
	{
		glUniform1i(GetUniformLocation(uniformName, programId), value);
	}

	void ShaderManager::SetUniformData(GLuint& programId, std::string uniformName, GLfloat& value)
	{
		glUniform1f(GetUniformLocation(uniformName, programId), value);
	}

	void ShaderManager::SetUniformData(GLuint& programId, std::string uniformName, glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(uniformName, programId), value.x, value.y);
	}

	void ShaderManager::SetUniformData(GLuint& programId, std::string uniformName, glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(uniformName, programId), value.x, value.y, value.z);
	}

	void ShaderManager::SetUniformData(GLuint& programId, std::string uniformName, glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(uniformName, programId), value.x, value.y, value.z, value.w);
	}

	void ShaderManager::SetUniformData(GLuint& programId, std::string uniformName, glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(uniformName, programId), 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderManager::CheckShaderCompilationResult(const GLuint& shader, bool& successful)
	{
		successful = true;
		GLint compilationResult;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationResult);

		if (compilationResult == GL_FALSE)
		{
			successful = false;

			// Storing the info log length of the specified shader into messageLength
			GLint messageLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLength);

			// Storing the infoLog of the specified shader into logMessage
			GLchar logMessage[2000];
			glGetShaderInfoLog(shader, messageLength, &messageLength, logMessage);

			std::cerr << "[ERROR] Shader Compile Error!" << std::endl;
			std::cerr << logMessage << std::endl;
		}
	}

	GLint ShaderManager::GetUniformLocation(std::string uniformName, GLuint programId)
	{
		GLint location = -1;

		auto foundIterator = ShaderUniformCache.find(uniformName);
		if (foundIterator == ShaderUniformCache.end())
		{
			location = glGetUniformLocation(programId, uniformName.c_str());
			ShaderUniformCache[uniformName] = location;
		}
		else
		{
			location = ShaderUniformCache[uniformName];
		}

		// TODO: Integrate this into log handling when implemented
		if (location == -1)
			std::cerr << "[ERROR] Failed to get Uniform Location for: " << uniformName << std::endl;

		return location;
	}
}