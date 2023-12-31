#include "include/SpaceObject.h"


SpaceObject::SpaceObject(const std::string& fileName, const char* name, 
						glm::vec3& initialPosition, glm::vec3& initialVelocity,
						float radius, float mass, 
						float scale, 
						float rotationPeriod,
						float inclination)
	: mFileName(fileName)
	, mName(nullptr)
	, mInitialPosition(initialPosition)
	, mCurrentPosition(initialPosition)
	, mInitialVelocity(initialVelocity)
	, mRadius(radius)
	, mMass(mass)
	, mScale(scale)
	, mRotationPeriod(rotationPeriod)
	, mGravitionalConstant(6.6743e-20)
	, mAxis(glm::vec3(0.f, 1.f, 0.f))
	, mAccumulatedRotationTime(0.f)
	, mInclination (inclination) {
	mName = new char[strlen(name) + 1];
	memcpy(mName, name, strlen(name) + 1);
	mName[strlen(name)] = '\0';
	mMu = mGravitionalConstant * mMass;

	glm::mat4 rotationMat(1.f);
	rotationMat = glm::rotate(rotationMat, mInclination, glm::vec3(0.f, 0.f, -1.f));
	mAxis = glm::vec3(rotationMat * glm::vec4(mAxis, 1.f));
}

SpaceObject::~SpaceObject() {
	delete[] mName; 
	mName = nullptr;
}

const std::string& SpaceObject::GetFilePath() const {
	return mFileName;
}

void SpaceObject::Update(GLuint uniformWorldLocation, GLfloat delta, GLfloat periodToScale) {
	glm::mat4 model(1.f);
	model = Translate(model);
	model = Rotate(model, delta, periodToScale);
	model = Scale(model);
	glUniformMatrix4fv(uniformWorldLocation, 1, GL_FALSE, glm::value_ptr(model));
}

const char* SpaceObject::GetName() const {
	return mName;
}

float SpaceObject::GetMu() const {
	return mMu;
}

glm::vec3 SpaceObject::GetCurrentPosition() const {
	return mCurrentPosition;
}

glm::mat4 SpaceObject::Translate(glm::mat4& model) {
	GLfloat scale = glm::length(mCurrentPosition) / EARTH_SUN_DISTANCE;
	if (scale > 1.f) {
		GLfloat value = glm::log(scale) + 1;
		return glm::translate(model, mCurrentPosition * (DISTANCE_SCALE / value) / EARTH_SUN_DISTANCE);
	}
	return glm::translate(model, (mCurrentPosition * DISTANCE_SCALE) / EARTH_SUN_DISTANCE);
}

glm::mat4 SpaceObject::Rotate(glm::mat4& model, GLfloat delta, GLfloat periodToScale) {
	float rotationProportion = mRotationPeriod / periodToScale;
	mAccumulatedRotationTime += mRotationPeriod * delta / (rotationProportion * EARTH_REVOLUTION_SIMULATION_PERIOD);
	if (mAccumulatedRotationTime > mRotationPeriod) {
		mAccumulatedRotationTime -= mRotationPeriod;
	}
	return glm::rotate(model, 2 * glm::pi<float>() * mAccumulatedRotationTime / mRotationPeriod, mAxis);
}

glm::mat4 SpaceObject::Scale(glm::mat4& model) {
	return glm::scale(model, glm::vec3(mScale, mScale, mScale));
}
