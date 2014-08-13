#pragma once

#ifndef _SHADEREXCEPTION_CLASS_HEADER_
#define _SHADEREXCEPTION_CLASS_HEADER_

#include <string>

class ShaderException
{
public:
	std::string Message;

	ShaderException(std::string ErrorMessage);
	~ShaderException();
};

#endif