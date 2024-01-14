#pragma once

#include <glm/gtx/rotate_vector.hpp>

#include "SpaceObject.h"

#include <vector>

typedef struct RevolutionObjectParams {
	spaceObjectParams_t base;
	float eccentricity;
	float centralBodyMu;
} revolutionObjectParams_t;

class RevolutionObject : public SpaceObject {
public:
	RevolutionObject() = delete;
	RevolutionObject(revolutionObjectParams_t& revolutionObjectParams);
	virtual ~RevolutionObject() = default;

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