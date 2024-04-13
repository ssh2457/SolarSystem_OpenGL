#pragma once

#include <glm/gtx/rotate_vector.hpp>

#include "CelestialBody.h"

#include <vector>

typedef struct RevolutionableBodyParams {
	celestialBodyParams_t base;
	float eccentricity;
	float semiMajorLength;
	float centralBodyMu;
} revolutionableBodyParams_t;

class RevolutionableBody : public CelestialBody{
public:
	RevolutionableBody() = delete;
	virtual ~RevolutionableBody() = default;

	void Revolve(GLfloat delta, GLfloat periodToScale, const glm::vec3& nearFociPos);
	float GetRevolutionPeriod() const;
	void CalcTrajectory(glm::vec3& nearFociPos);

protected:
	RevolutionableBody(revolutionableBodyParams_t& revolutionableBodyParams);

	float mRevolutionPeriod;
	float mEccentricity;
	float mSemiMajorLength;
	float mAccumulatedRevolutionTime;
	float mVelocity;

	void CalcRevolutionPeriod(float centralBodyMu);
	float CalcEccentricAnomaly(float meanAnomaly);
};
