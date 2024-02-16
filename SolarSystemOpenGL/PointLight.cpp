#include "include/PointLight.h"

PointLight::PointLight()
	: Light()
	, mPosition(glm::vec3(0.f, 0.f, 0.f))
	, mConstant(1.f)
	, mLinear(0.f)
	, mExponent(0.f) {
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat ambientIntensity, GLfloat diffuseIntensity,
	GLfloat posX, GLfloat posY, GLfloat posZ,
	GLfloat con, GLfloat lin, GLfloat exp)
	: Light(red, green, blue,
		ambientIntensity, diffuseIntensity)
	, mPosition(glm::vec3(posX, posY, posZ))
	, mConstant(con)
	, mLinear(lin)
	, mExponent(exp) {

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