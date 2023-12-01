#pragma once

#include <gl/glew.h>
#include <spdlog/spdlog.h>

#include <string>
#include <fstream>

#include "include/Common.h"


class Shader {
public:
	Shader();
	virtual ~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexPath, const char* fragmentPath);
	std::string ReadFile(const char* filePath);

	void UseShader();
	void ClearShader();

	GLuint GetWorldLocation() const;
	GLuint GetViewLocation() const;
	GLuint GetProjectionLocation() const;
	GLuint GetCameraPositionLocation() const;

private:
	GLuint mShaderID, mUniformProjection, mUniformWorld, mUniformView, mUniformCameraPosition;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
