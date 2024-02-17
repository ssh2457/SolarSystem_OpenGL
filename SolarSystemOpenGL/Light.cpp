#include "include/Light.h"

/*
Light::Light()
	: mColour(glm::vec3(1.f, 1.f, 1.f))
	, mAmbientIntensity(1.f)
	, mDiffuseIntensity(0.f)
	, mLightProjection(glm::mat4(1.f))
	, mShadowMap(nullptr) 
{
	mShadowMap = std::make_unique<ShadowMap>();
	mShadowMap->Init(800, 600);
}
*/


Light::Light(const lightParams_t& lightParams)
	: mColour(glm::vec3(lightParams.red, lightParams.green, lightParams.blue))
	, mAmbientIntensity(lightParams.ambientIntensity)
	, mDiffuseIntensity(lightParams.diffuseIntensity) 
	, mLightProjection(glm::mat4(1.f))
{
	mShadowMap = std::make_unique<ShadowMap>();
	mShadowMap->Init(lightParams.shadowMapParams.width, lightParams.shadowMapParams.height);
}

Light::~Light() {

}