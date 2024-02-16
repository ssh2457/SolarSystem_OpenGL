#pragma once

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
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat ambientIntensity, GLfloat diffuseIntensity,
		GLfloat posX, GLfloat posY, GLfloat posZ,
		GLfloat con, GLfloat lin, GLfloat exp);
	virtual ~PointLight() = default;
	void UseLight(GLuint colourLocation,
		GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation,
		GLuint positionLocation,
		GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);
private:
	glm::vec3 mPosition;
	GLfloat mConstant, mLinear, mExponent;

	// pointlight attenuation equation:
	// Exponent * x^2 + Linear * x + Constant
};