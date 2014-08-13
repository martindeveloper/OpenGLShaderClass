#include "ShaderException.h"

ShaderException::ShaderException(std::string ErrorMessage)
{
	this->Message = ErrorMessage;
}

ShaderException::~ShaderException()
{
}
