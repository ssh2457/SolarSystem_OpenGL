#include "include/CelestialBody.h"

#include <limits>

CelestialBody::CelestialBody(const celestialBodyParams_t& celestialBodyParams)
	: mFileName(celestialBodyParams.fileName)
	, mName(nullptr)
	, mInitialPosition(celestialBodyParams.initialPosition)
	, mCurrentPosition(celestialBodyParams.initialPosition)
	, mInitialVelocity(celestialBodyParams.initialVelocity)
	, mRadius(celestialBodyParams.radius)
	, mMass(celestialBodyParams.mass)
	, mScale(celestialBodyParams.scale)
	, mRotationPeriod(celestialBodyParams.rotationPeriod)
	, mGravitionalConstant(6.6743e-20)
	, mAccumulatedRotationTime(0.f)
	, mInclination (celestialBodyParams.inclination)
	, mSimulationInitialDistance(celestialBodyParams.simulationInitialDistance)
	, mSimulationPosition(glm::vec3(0, 0, 0))
{
	mName = new char[strlen(celestialBodyParams.name) + 1];
	memcpy(mName, celestialBodyParams.name, strlen(celestialBodyParams.name) + 1);
	mName[strlen(celestialBodyParams.name)] = '\0';
	mMu = mGravitionalConstant * mMass;
}

CelestialBody::~CelestialBody() {
	delete[] mName; mName = nullptr;
}

const std::string& CelestialBody::GetFilePath() const {
	return mFileName;
}

void CelestialBody::Update(GLuint uniformWorldLocation, GLfloat delta, GLfloat periodToScale, CelestialBody* governingObj) {
	glm::mat4 model(1.f);

	if (governingObj == nullptr) {
		model = Translate(model);
	}
	else {
		model = TranslateFromGoverningObj(model, governingObj);
	}

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

glm::vec3 CelestialBody::GetInitialPosition() const
{
	return mInitialPosition;
}

glm::mat4 CelestialBody::Translate(glm::mat4& model) {
	if (glm::length(mInitialPosition) < std::numeric_limits<float>::epsilon()) {
		return glm::translate(model, mInitialPosition);
	}

	
	float ratio = glm::length(mCurrentPosition) / glm::length(mInitialPosition);
	glm::vec3 unitVec = glm::normalize(mCurrentPosition);
	mSimulationPosition = unitVec * ratio * mSimulationInitialDistance;

	/*
	if (std::string(mName) == "Earth") {
		SPDLOG_INFO("{} simulation position[x, y, z]: [{}, {}, {}]", std::string(mName), mSimulationPosition.x, mSimulationPosition.y, mSimulationPosition.z);
	}
	*/

	return glm::translate(model, mSimulationPosition);
}

glm::mat4 CelestialBody::TranslateFromGoverningObj(glm::mat4& model, CelestialBody* governingObj)
{
	if (governingObj == nullptr) {
		assert(false);
	}
	
	float ratio = glm::length(mCurrentPosition) / glm::length(mInitialPosition);
	float distance = glm::abs(mSimulationInitialDistance - governingObj->mSimulationInitialDistance);

	glm::vec3 rel_unit_vec = mCurrentPosition - governingObj->mCurrentPosition;
	rel_unit_vec = glm::normalize(rel_unit_vec);

	glm::vec3 rel_simul_pos = ratio * distance * rel_unit_vec;

	mSimulationPosition = governingObj->mSimulationPosition + rel_simul_pos;
	//SPDLOG_INFO("{} simulation position[x, y, z]: [{}, {}, {}]", std::string(mName), mSimulationPosition.x, mSimulationPosition.y, mSimulationPosition.z);

	return glm::translate(model, mSimulationPosition);
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
