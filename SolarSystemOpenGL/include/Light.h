#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

typedef struct LightParams {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
} lightParams_t;

class Light {
public:
	Light();
	Light(const lightParams_t& lightParams);
	virtual ~Light();

protected:
	glm::vec3 mColour;
	GLfloat mAmbientIntensity;
	GLfloat mDiffuseIntensity;
};