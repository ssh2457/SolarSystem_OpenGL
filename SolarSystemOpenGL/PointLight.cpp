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

PointLight::PointLight(const pointLightParams_t& pointLightParams, GLfloat nearPlane, GLfloat farPlane)
	: Light(pointLightParams.base)
	, mPosition(glm::vec3(pointLightParams.posX, pointLightParams.posY, pointLightParams.posZ))
	, mConstant(pointLightParams.con)
	, mLinear(pointLightParams.lin)
	, mExponent(pointLightParams.exp) 
	, mFarPlane(farPlane)
{
	float aspect = pointLightParams.base.shadowMapParams.width / (float)pointLightParams.base.shadowMapParams.height;
	mLightProjection = glm::perspective(glm::radians(90.f), aspect, nearPlane, mFarPlane);

	
	if (mShadowMap) {
		mShadowMap = nullptr;
	}

	mShadowMap = std::make_unique<OmniShadowMap>();
	mShadowMap->Init(pointLightParams.base.shadowMapParams.width, pointLightParams.base.shadowMapParams.height);
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

void PointLight::SetPosition(const glm::vec3& position)
{
	mPosition.x = position.x;
	mPosition.y = position.y;
	mPosition.z = position.z;
}

std::vector<glm::mat4> PointLight::CalcLightTransform()
{
	std::vector<glm::mat4> lightTransforms;


	// +x, -x
	lightTransforms.push_back(mLightProjection * glm::lookAt(mPosition, mPosition + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	lightTransforms.push_back(mLightProjection * glm::lookAt(mPosition, mPosition + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));

	// +y, -y
	lightTransforms.push_back(mLightProjection * glm::lookAt(mPosition, mPosition + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	lightTransforms.push_back(mLightProjection * glm::lookAt(mPosition, mPosition + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));

	// +z, -z
	lightTransforms.push_back(mLightProjection * glm::lookAt(mPosition, mPosition + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	lightTransforms.push_back(mLightProjection * glm::lookAt(mPosition, mPosition + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	return lightTransforms;
}
