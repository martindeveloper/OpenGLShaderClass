#pragma once

#ifndef _SHADER_CLASS_HEADER_
#define _SHADER_CLASS_HEADER_

#include <string>
#include <Windows.h>
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "ShaderException.h"

class Shader{
public:
	Shader(const char *VertexPath, const char *FragmentPath);
	~Shader();

	void Compile();
	GLuint GetProgramID();
	bool IsShaderCompiled();
	bool DebugEnabled = true;

private:
	GLuint VertexShader;
	GLuint FragmentShader;

	std::string VertexShaderString;
	std::string FragmentShaderString;

	const char *VertexShaderSource;
	const char *FragmentShaderSource;

	bool bShaderIsCompiled = false;
	GLuint ShaderProgramID;

	std::string ReadFile(const char *FilePath);
	GLint CheckCompilation(GLuint CompiledShader);
};

#endif