#pragma once

#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include <string>
#include <fstream>

#include "Common.h"
#include "PointLight.h"

class SimpleShader {
public:
	SimpleShader();
	virtual ~SimpleShader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	virtual void CreateFromFiles(const char* vertexPath, const char* fragmentPath);
	std::string ReadFile(const char* filePath);

	void Validate();

	void UseShader();
	virtual void ClearShader();

	GLuint GetWorldLocation() const;
	GLuint GetBindingPoint() const;
protected:
	GLuint mShaderID, mUniformWorld, mUniformBlock, mBindingPoint;
	virtual void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};