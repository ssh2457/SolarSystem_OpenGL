#include "include/SpaceObject.h"

SpaceObject::SpaceObject(const std::string& fileName, const char* name, 
						glm::vec3& initialPosition, glm::vec3& initialVelocity,
						float radius, float mass, 
						float scale, 
						float rotationPeriod)
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
	, mRotationAngle(0.f) {
	mName = new char[strlen(name) + 1];
	memcpy(mName, name, strlen(name) + 1);
	mName[strlen(name)] = '\0';
	mMu = mGravitionalConstant * mMass;
}

SpaceObject::~SpaceObject() {
	delete[] mName; 
	mName = nullptr;
}

const std::string& SpaceObject::GetFilePath() const {
	return mFileName;
}

void SpaceObject::Update(GLuint uniformWorldLocation, GLfloat time) {
	glm::mat4 model(1.f);
	model = Translate(model);
	model = Rotate(model, time);
	model = Scale(model);
	glUniformMatrix4fv(uniformWorldLocation, 1, GL_FALSE, glm::value_ptr(model));
}

float SpaceObject::GetMu() const {
	return mMu;
}

glm::mat4 SpaceObject::Translate(glm::mat4 model) {
	return glm::translate(model, (mCurrentPosition * DISTANCE_SCALE) / EARTH_SUN_DISTANCE);
}

glm::mat4 SpaceObject::Rotate(glm::mat4 model, GLfloat time) {
	mRotationAngle += mRotationPeriod * time;
	if (mRotationAngle > 360.f) {
		mRotationAngle = 0.f;
	}
	return glm::rotate(model, mRotationAngle, mAxis);
}

glm::mat4 SpaceObject::Scale(glm::mat4 model) {
	return glm::scale(model, glm::vec3(mScale, mScale, mScale));
}
