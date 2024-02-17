#include "include/PointLight.h"

/*
PointLight::PointLight()
	: Light()
	, mPosition(glm::vec3(0.f, 0.f, 0.f))
	, mConstant(1.f)
	, mLinear(0.f)
	, mExponent(0.f) {
}
*/

PointLight::PointLight(const pointLightParams_t& pointLightParams)
	: Light(pointLightParams.base)
	, mPosition(glm::vec3(pointLightParams.posX, pointLightParams.posY, pointLightParams.posZ))
	, mConstant(pointLightParams.con)
	, mLinear(pointLightParams.lin)
	, mExponent(pointLightParams.exp) 
{
}

void PointLight::UseLight(GLuint colourLocation,
	GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation,
	GLuint positionLocation,
	GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation) {
	glUniform3f(colourLocation, mColour.x, mColour.y, mColour.z);

	glUniform1f(ambientIntensityLocation, mAmbientIntensity);
	glUniform1f(diffuseIntensityLocation, mDiffuseIntensity);

	glUniform3f(positionLocation, mPosition.x, mPosition.y, mPosition.z);

	glUniform1f(constantLocation, mConstant);
	glUniform1f(linearLocation, mLinear);
	glUniform1f(exponentLocation, mExponent);
}

void PointLight::SetPosition(glm::vec3& position)
{
	mPosition.x = position.x;
	mPosition.y = position.y;
	mPosition.z = position.z;
}