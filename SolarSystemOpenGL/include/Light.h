#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "ShadowMap.h"

typedef struct LightParams {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	shadowMapParams_t shadowMapParams;
} lightParams_t;

class Light {
public:
	Light() = delete;
	Light(const lightParams_t& lightParams);
	virtual ~Light();

	ShadowMap* GetShadowMap() const { return mShadowMap.get(); }

protected:
	glm::vec3 mColour;
	GLfloat mAmbientIntensity;
	GLfloat mDiffuseIntensity;

	glm::mat4 mLightProjection;
	std::unique_ptr<ShadowMap> mShadowMap;
};