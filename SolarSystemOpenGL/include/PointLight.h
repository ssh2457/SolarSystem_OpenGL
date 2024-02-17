#pragma once

#include "glm\gtc\matrix_transform.hpp"

#include "Light.h"

typedef struct PointLightParams {
	lightParams_t base;

	GLfloat posX;
	GLfloat posY;
	GLfloat posZ;

	GLfloat con;
	GLfloat lin;
	GLfloat exp;
} pointLightParams_t;

class PointLight : public Light {
public:
	PointLight() = delete;
	PointLight(const pointLightParams_t& pointLightParams);
	virtual ~PointLight() = default;
	void UseLight(GLuint colourLocation,
		GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation,
		GLuint positionLocation,
		GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

	glm::vec3 GetPosition() const { return mPosition; }
	void SetPosition(glm::vec3& position);

private:
	glm::vec3 mPosition;
	GLfloat mConstant, mLinear, mExponent;

	// pointlight attenuation equation:
	// Exponent * x^2 + Linear * x + Constant
};