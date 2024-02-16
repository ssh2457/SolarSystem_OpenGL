#pragma once

#include <gl/glew.h>
#include <spdlog/spdlog.h>

#include <string>
#include <fstream>

#include "Common.h"
#include "PointLight.h"
#include "SimpleShader.h"

class Shader : public SimpleShader {
public:
	Shader();
	virtual ~Shader();

	virtual void ClearShader() override;

	GLuint GetCameraPositionLocation() const;

	GLuint GetLightCoulourLocation() const;

	GLuint GetAmbientIntensityLocation() const;
	GLuint GetDiffuseIntensityLocation() const;

	GLuint GetLightPositionLocation() const;


	GLuint GetConstantLocation() const;
	GLuint GetLinearLocation() const;
	GLuint GetExponentLocation() const;

	void SetPointLight(PointLight* light);

private:
	GLuint	mUniformCameraPosition,
		mUniformLightColour,
		mUniformAmbientIntensity, mUniformDiffuseIntensity,
		mUniformLightPosition,
		mUniformConstant, mUniformLinear, mUniformExponent;

	virtual void CompileShader(const char* vertexCode, const char* fragmentCode) override;
};