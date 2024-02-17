#pragma once

#include <gl/glew.h>
#include <spdlog/spdlog.h>

#include <glm/gtc/type_ptr.hpp>

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

	void SetTexture(const GLuint textureUnit); // for ShadowMap

private:
	GLuint	mUniformCameraPosition,
		mUniformLightColour,
		mUniformAmbientIntensity, mUniformDiffuseIntensity,
		mUniformLightPosition,
		mUniformConstant, mUniformLinear, mUniformExponent,
		mUniformTexture; // for ShadowMap

	virtual void CompileShader(const char* vertexCode, const char* fragmentCode) override;
};