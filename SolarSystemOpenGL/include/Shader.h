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

	GLuint GetCoulourLocation() const;

	GLuint GetAmbientIntensityLocation() const;
	GLuint GetDiffuseIntensityLocation() const;

	GLuint GetLightPositionLocation() const;


	GLuint GetConstantLocation() const;
	GLuint GetLinearLocation() const;
	GLuint GetExponentLocation() const;

private:
	GLuint mShaderID, mUniformProjection, mUniformWorld, mUniformView, mUniformCameraPosition,
			mUniformColour,
			mUniformAmbientIntensity, mUniformDiffuseIntensity, 
			mUniformLightPosition, 
			mUniformConstant, mUniformLinear, mUniformExponent;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
