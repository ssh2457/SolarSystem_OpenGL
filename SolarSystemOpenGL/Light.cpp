#include "include/Light.h"

Light::Light()
	: mColour(glm::vec3(1.f, 1.f, 1.f))
	, mAmbientIntensity(1.f)
	, mDiffuseIntensity(0.f) {

}


Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity)
	: mColour(glm::vec3(red, green, blue))
	, mAmbientIntensity(ambientIntensity)
	, mDiffuseIntensity(diffuseIntensity) {

}

Light::~Light() {

}