#include "include/SpaceObject.h"

SpaceObject::SpaceObject(const std::string& fileName, const char* name, glm::vec3& position, float scale, float rotationSpeed)
	: mFileName(fileName)
	, mName(nullptr)
	, mPosition(position)
	, mAxis(glm::vec3(0.f, 1.f, 0.f))
	, mScale(scale)
	, mRotationSpeed(rotationSpeed)
	, mRotationAngle(0.f) {


	mName = new char[strlen(name) + 1];
	memcpy(mName, name, strlen(name) + 1);
	mName[strlen(name)] = '\0';

}

SpaceObject::~SpaceObject() {
	delete[] mName; 
	mName = nullptr;
}

const std::string& SpaceObject::GetFilePath() const {
	return mFileName;
}

void SpaceObject::Update(GLuint uniformWorldLocation, float time) {
	glm::mat4 model(1.f);
	model = Translate(model);
	model = Rotate(model, time);
	model = Scale(model);
	glUniformMatrix4fv(uniformWorldLocation, 1, GL_FALSE, glm::value_ptr(model));
}

glm::mat4 SpaceObject::Translate(glm::mat4 model) {
	return glm::translate(model, mPosition);
}

glm::mat4 SpaceObject::Rotate(glm::mat4 model, float time) {
	mRotationAngle += mRotationSpeed * time;
	if (mRotationAngle > 360.f) {
		mRotationAngle = 0.f;
	}
	return glm::rotate(model, mRotationAngle, mAxis);
}

glm::mat4 SpaceObject::Scale(glm::mat4 model) {
	return glm::scale(model, glm::vec3(mScale, mScale, mScale));
}
