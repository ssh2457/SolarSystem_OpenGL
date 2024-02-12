#pragma once

#include <glm/gtx/rotate_vector.hpp>

#include "CelestialBody.h"

#include <vector>

typedef struct SatelliteParams {
	celestialBodyParams_t base;
	float eccentricity;
	float semiMajorLength;
	float centralBodyMu;
} satelliteParams_t;

class Satellite : public CelestialBody {
public:
	Satellite() = delete;
	Satellite(satelliteParams_t& satelliteParams);
	virtual ~Satellite() = default;

	void Revolve(GLfloat delta, GLfloat periodToScale, glm::vec3& nearFociPos);
	float GetRevolutionPeriod() const;
	void CalcTrajectory(glm::vec3& nearFociPos);

private:
	float mRevolutionPeriod;
	float mEccentricity;
	float mSemiMajorLength;
	float mAccumulatedRevolutionTime;
	float mVelocity;

	std::vector<glm::vec3> mTrajectoryPts;

	void CalcRevolutionPeriod(float centralBodyMu);
	float CalcEccentricAnomaly(float meanAnomaly);
};