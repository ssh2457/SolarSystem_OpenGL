#include "include/Light.h"

Light::Light()
	: mColour(glm::vec3(1.f, 1.f, 1.f))
	, mAmbientIntensity(1.f)
	, mDiffuseIntensity(0.f) {

}


Light::Light(const lightParams_t& lightParams)
	: mColour(glm::vec3(lightParams.red, lightParams.green, lightParams.blue))
	, mAmbientIntensity(lightParams.ambientIntensity)
	, mDiffuseIntensity(lightParams.diffuseIntensity) {

}

Light::~Light() {

}