#include "ShaderProgram.h"
#include <iostream>
#include "../../file-io/DiskReader.h"

ShaderProgram::ShaderProgram()
{
	CreateShader();
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::AttachShader(ShaderTypes shaderType, std::string shaderPath)
{
	GLuint shader = 0;

	if (shaderType == ShaderTypes::VertexShader)
		shader = glCreateShader(GL_VERTEX_SHADER);
	else if (shaderType == ShaderTypes::FragmentShader)
		shader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string sourceString;
	DiskReader::ReadString(sourceString, shaderPath);
	const char* shaderSource = sourceString.c_str();

	// Setting the source code of the specified shader
	glShaderSource(shader, 1, &shaderSource, NULL);
	// Compiling the source code stored in the shader
	glCompileShader(shader);

	// >> Checking if shader compiled successfully <<
	// Storing the compilation status of the specified shader into compilationResult
	GLint compilationResult;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationResult);

	if (compilationResult == GL_FALSE)
	{
		// Storing the info log length of the specified shader into messageLength
		GLint messageLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLength);

		// Storing the infoLog of the specified shader into logMessage
		std::string logMessage;
		glGetShaderInfoLog(shader, messageLength, &messageLength, &logMessage[0]);

		std::cerr << "[ERROR]: Shader Compile Error!" << std::endl;
		if (shaderType == ShaderTypes::VertexShader)
			std::cerr << "Shader Type: Vertex Shader" << std::endl;
		else if (shaderType == ShaderTypes::FragmentShader)
			std::cerr << "Shader Type: Fragment Shader" << std::endl;
		std::cerr << "Shader Path: " << shaderPath << std::endl;
		std::cerr << logMessage << std::endl;

		// If the shader failed to compile it is pointless to keep it in the GPU
		glDeleteShader(shader);
		return;
	}

	glAttachShader(ProgramId, shader);
	Shaders.emplace_back(shader);
}

void ShaderProgram::CreateShader()
{
	ProgramId = glCreateProgram();
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(ProgramId);
	glValidateProgram(ProgramId);

	// We no longer need to store individual shaders as we have a working program
	for (GLuint shader : Shaders)
	{
		glDeleteShader(shader);
	}

	Shaders.clear();
}

void ShaderProgram::UseProgram()
{
	glUseProgram(ProgramId);
}

void ShaderProgram::UnbindProgram()
{
	glUseProgram(0);
}

void ShaderProgram::SetUniformData(std::string uniformName, GLint& value)
{
	glUniform1i(GetUniformLocation(uniformName), value);
}

void ShaderProgram::SetUniformData(std::string uniformName, GLfloat& value)
{
	glUniform1f(GetUniformLocation(uniformName), value);
}

void ShaderProgram::SetUniformData(std::string uniformName, glm::vec2& value)
{
	glUniform2f(GetUniformLocation(uniformName), value.x, value.y);
}

void ShaderProgram::SetUniformData(std::string uniformName, glm::vec3& value)
{
	glUniform3f(GetUniformLocation(uniformName), value.x, value.y, value.z);
}

void ShaderProgram::SetUniformData(std::string uniformName, glm::vec4& value)
{
	glUniform4f(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w);
}

void ShaderProgram::SetUniformData(std::string uniformName, glm::mat4& value)
{
	glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::DeleteProgram()
{
	glDeleteProgram(ProgramId);
}

GLint ShaderProgram::GetUniformLocation(std::string uniformName)
{
	GLint location = -1;

	auto foundIterator = ShaderUniformCache.find(uniformName);
	if (foundIterator == ShaderUniformCache.end())
	{
		location = glGetUniformLocation(ProgramId, uniformName.c_str());
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