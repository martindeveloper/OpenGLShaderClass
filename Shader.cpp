#pragma once

#include "Shader.h"

Shader::Shader(const char *VertexPath, const char *FragmentPath)
{
	this->FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	this->VertexShader = glCreateShader(GL_VERTEX_SHADER);

	this->VertexShaderString = this->ReadFile(VertexPath);
	this->FragmentShaderString = this->ReadFile(FragmentPath);

	this->VertexShaderSource = VertexShaderString.c_str();
	this->FragmentShaderSource = FragmentShaderString.c_str();
}

Shader::~Shader()
{
	glDeleteShader(this->VertexShader);
	glDeleteShader(this->FragmentShader);
}

GLint Shader::CheckCompilation(GLuint CompiledShader)
{
	GLint CompileResult = GL_FALSE;
	int LogLength;

	glGetShaderiv(CompiledShader, GL_COMPILE_STATUS, &CompileResult);
	glGetShaderiv(CompiledShader, GL_INFO_LOG_LENGTH, &LogLength);
	std::vector<char> ShaderError(LogLength);
	glGetShaderInfoLog(CompiledShader, LogLength, NULL, &ShaderError[0]);
	std::cout << "Check error: " << &ShaderError[0] << std::endl;

	return CompileResult;
}

void Shader::Compile()
{
	glShaderSource(this->VertexShader, 1, &this->VertexShaderSource, NULL);
	glCompileShader(this->VertexShader);

	if (this->DebugEnabled)
	{
		// Check vertex shader
		std::cout << "Compiling vertex shader." << std::endl;
		this->CheckCompilation(this->VertexShader);
	}

	glShaderSource(this->FragmentShader, 1, &this->FragmentShaderSource, NULL);
	glCompileShader(this->FragmentShader);

	if (this->DebugEnabled)
	{
		// Check fragment shader
		std::cout << "Compiling fragment shader." << std::endl;
		this->CheckCompilation(this->FragmentShader);
	}

	if (this->DebugEnabled)
	{
		std::cout << "Linking program" << std::endl;
	}

	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, this->VertexShader);
	glAttachShader(ShaderProgram, this->FragmentShader);
	glLinkProgram(ShaderProgram);

	this->bShaderIsCompiled = true;

	this->ShaderProgramID = ShaderProgram;
}

bool Shader::IsShaderCompiled()
{
	return this->bShaderIsCompiled;
}

GLuint Shader::GetProgramID()
{
	if (!this->IsShaderCompiled())
	{
		throw new ShaderException("Shader is not compiled yet!");
	}

	return ShaderProgramID;
}

std::string Shader::ReadFile(const char *FilePath)
{
	std::string content;
	std::ifstream FileStream(FilePath, std::ios::in);

	if (!FileStream.is_open()) {
		throw new ShaderException("Can not open shader file!");
	}

	std::string line = "";
	while (!FileStream.eof()) {
		std::getline(FileStream, line);
		content.append(line + "\n");
	}

	FileStream.close();
	return content;
}