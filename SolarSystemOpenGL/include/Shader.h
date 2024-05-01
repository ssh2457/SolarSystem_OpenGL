#pragma once

#include <GL/glew.h>
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

	virtual void CreateFromFiles(const char* vertexPath, const char* fragmentPath) override;
	virtual void CreateFromFiles(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
	

	GLuint GetCameraPositionLocation() const;

	GLuint GetLightCoulourLocation() const;

	GLuint GetAmbientIntensityLocation() const;
	GLuint GetDiffuseIntensityLocation() const;

	GLuint GetLightPositionLocation() const;


	GLuint GetConstantLocation() const;
	GLuint GetLinearLocation() const;
	GLuint GetExponentLocation() const;

	GLuint GetOmniLightPosLocation() const { return mUniformOmniLightPos; }
	GLuint GetFarPlaneLocation() const { return mUniformFarPlane; }

	void SetPointLight(PointLight* light, GLuint textureUnit);

	void SetTexture(const GLuint textureUnit); // for ShadowMap

	void SetLightMatrices(std::vector<glm::mat4> lightMatrices);

private:
	GLuint	mUniformCameraPosition,
		mUniformLightColour,
		mUniformAmbientIntensity, mUniformDiffuseIntensity,
		mUniformLightPosition,
		mUniformConstant, mUniformLinear, mUniformExponent,
		mUniformTexture,
		mUniformOmniLightPos, mUniformFarPlane; // for ShadowMap

	GLuint mUniformLightMatrices[6];

	struct {
		GLuint shadowMap;
		GLuint farPlane;
	} mUniformOmniShadowMap;

	virtual void CompileShader(const char* vertexCode, const char* fragmentCode) override;
	void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);

};