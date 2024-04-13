#pragma once

#include <spdlog/spdlog.h>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Model.h"
#include "Common.h"



typedef struct CelestialBodyParams {
	std::string fileName;
	const char* name;
	glm::vec3 initialPosition;
	glm::vec3 initialVelocity;
	float radius;
	float mass;
	float scale;
	float rotationPeriod;
	float inclination;
	float simulationInitialDistance;
} celestialBodyParams_t;


class CelestialBody : public Model {
public:
	CelestialBody() = delete;
	CelestialBody(const celestialBodyParams_t& celestialBodyParams);
	virtual ~CelestialBody();

	const std::string& GetFilePath() const;

	void Update(GLuint uniformWorldLocation, GLfloat delta, GLfloat periodToScale, CelestialBody* governingObj = nullptr);

	const char* GetName() const;
	float GetMu() const;
	glm::vec3 GetCurrentPosition() const;
	glm::vec3 GetInitialPosition() const;

protected:
	const std::string mFileName;
	char* mName;
	glm::vec3 mInitialPosition;
	glm::vec3 mCurrentPosition;
	glm::vec3 mInitialVelocity;
	float mScale;
	float mRadius;
	float mMass;
	const float mGravitionalConstant;
	float mMu;
	float mInclination;
	float mSimulationInitialDistance;
	glm::vec3 mSimulationPosition;

	float mAccumulatedRotationTime;
	float mRotationPeriod;

	glm::mat4 Translate(glm::mat4& model);
	glm::mat4 TranslateFromGoverningObj(glm::mat4& model, CelestialBody* governingObj = nullptr);
	glm::mat4 Rotate(glm::mat4& model, GLfloat delta, GLfloat periodToScale);
	glm::mat4 Scale(glm::mat4& model);
	glm::mat4 Incline(glm::mat4& model);
};