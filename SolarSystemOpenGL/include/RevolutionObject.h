#pragma once

#include <glm/gtx/rotate_vector.hpp>

#include "Star.h"
#include "SpaceObject.h"

class RevolutionObject : public SpaceObject {
public:
	RevolutionObject() = delete;
	RevolutionObject(const std::string& fileName, const char* name,
					glm::vec3& positionAtPeriapsis, glm::vec3& velocityAtPeriapsis,
					float radius, float mass,
					float scale, 
					float rotationPeriod,
					float eccentricity,
					float centralBodyMu);
	virtual ~RevolutionObject() = default;

	void CalcRevolutionPeriod(float centralBodyMu);
	void Revolve(float centralBodyMu, GLfloat time);
private:
	float mRevolutionPeriod;
	float mEccentricity;
	float mSemiMajorLength;
	float mPeriod;
	float mVelocity;

	float CalcEccentricAnomaly(float meanAnomaly);
};