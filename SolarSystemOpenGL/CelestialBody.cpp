#include "include/CelestialBody.h"

#include <limits>


CelestialBody::CelestialBody(const std::string& fileName, const char* name,
						glm::vec3& initialPosition, glm::vec3& initialVelocity,
						float radius, float mass, 
						float scale, 
						float rotationPeriod,
						float inclination,
						float simulationInitialDistance)
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
	, mAccumulatedRotationTime(0.f)
	, mInclination (inclination)
	, mSimulationInitialDistance(simulationInitialDistance)
{
	mName = new char[strlen(name) + 1];
	memcpy(mName, name, strlen(name) + 1);
	mName[strlen(name)] = '\0';
	mMu = mGravitionalConstant * mMass;
}

CelestialBody::~CelestialBody() {
	delete[] mName; mName = nullptr;
}

const std::string& CelestialBody::GetFilePath() const {
	return mFileName;
}

void CelestialBody::Update(GLuint uniformWorldLocation, GLfloat delta, GLfloat periodToScale) {
	glm::mat4 model(1.f);
	model = Translate(model);
	model = Incline(model);
	model = Rotate(model, delta, periodToScale);
	model = Scale(model);
	
	glUniformMatrix4fv(uniformWorldLocation, 1, GL_FALSE, glm::value_ptr(model));
}

const char* CelestialBody::GetName() const {
	return mName;
}

float CelestialBody::GetMu() const {
	return mMu;
}

glm::vec3 CelestialBody::GetCurrentPosition() const {
	return mCurrentPosition;
}

glm::mat4 CelestialBody::Translate(glm::mat4& model) {
	if (glm::length(mInitialPosition) < std::numeric_limits<float>::epsilon()) {
		return glm::translate(model, mInitialPosition);
	}
	float ratio = glm::length(mCurrentPosition) / glm::length(mInitialPosition);
	glm::vec3 unitVec = glm::normalize(mCurrentPosition);
	glm::vec3 simulPos = unitVec * ratio * mSimulationInitialDistance;

	if (std::string(mName) == "Moon") {
		SPDLOG_INFO("Moon's real position(x, y, z): {}, {}, {}", mCurrentPosition.x, mCurrentPosition.y, mCurrentPosition.z);
		SPDLOG_INFO("Moon's simulation position(x, y, z): {}, {}, {}", simulPos.x, simulPos.y, simulPos.z);
	}

	if (std::string(mName) == "Earth") {
		SPDLOG_INFO("Earth's real position(x, y, z): {}, {}, {}", mCurrentPosition.x, mCurrentPosition.y, mCurrentPosition.z);
		SPDLOG_INFO("Earth's simulation position(x, y, z): {}, {}, {}", simulPos.x, simulPos.y, simulPos.z);
	}

	return glm::translate(model, simulPos);
}

glm::mat4 CelestialBody::Rotate(glm::mat4& model, GLfloat delta, GLfloat periodToScale) {
	float rotationProportion = mRotationPeriod / periodToScale;
	mAccumulatedRotationTime += mRotationPeriod * delta / (rotationProportion * EARTH_REVOLUTION_SIMULATION_PERIOD);
	if (mAccumulatedRotationTime > mRotationPeriod) {
		mAccumulatedRotationTime -= mRotationPeriod;
	}

	return glm::rotate(model, 2 * glm::pi<float>() * mAccumulatedRotationTime / mRotationPeriod, glm::vec3(0.f, 1.f, 0.f));
}

glm::mat4 CelestialBody::Scale(glm::mat4& model) {
	return glm::scale(model, glm::vec3(mScale, mScale, mScale));
}

glm::mat4 CelestialBody::Incline(glm::mat4& model)
{
	return glm::rotate(model, mInclination, glm::vec3(0.f, 0.f, -1.f));
}
