#pragma once

#include <glm/gtx/rotate_vector.hpp>

#include "SpaceObject.h"

typedef struct RevolutionObjectParams {
	spaceObjectParams_t base;
	float eccentricity;
	float centralBodyMu;
} revolutionObjectParams_t;

class RevolutionObject : public SpaceObject {
public:
	RevolutionObject() = delete;
	/*
	RevolutionObject(const std::string& fileName, const char* name,
					glm::vec3& positionAtPeriapsis, glm::vec3& velocityAtPeriapsis,
					float radius, float mass,
					float scale, 
					float rotationPeriod,
					float eccentricity,
					float centralBodyMu);
					*/
	RevolutionObject(revolutionObjectParams_t& revolutionObjectParams);
	virtual ~RevolutionObject() = default;

	void CalcRevolutionPeriod(float centralBodyMu);
	void Revolve(float centralBodyMu, GLfloat delta, GLfloat periodToScale);
	float GetRevolutionPeriod() const;

private:
	float mRevolutionPeriod;
	float mEccentricity;
	float mSemiMajorLength;
	float mAccumulatedRevolutionTime;
	float mVelocity;

	float CalcEccentricAnomaly(float meanAnomaly);
};