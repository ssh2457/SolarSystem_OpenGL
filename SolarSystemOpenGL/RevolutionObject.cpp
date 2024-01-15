#include "include/RevolutionObject.h"

RevolutionObject::RevolutionObject(revolutionObjectParams_t& revolutionObjectParams)
	: SpaceObject(revolutionObjectParams.base.fileName, revolutionObjectParams.base.name,
		revolutionObjectParams.base.initialPosition, revolutionObjectParams.base.initialVelocity,
		revolutionObjectParams.base.radius, revolutionObjectParams.base.mass,
		revolutionObjectParams.base.scale, revolutionObjectParams.base.rotationPeriod, revolutionObjectParams.base.inclination)
	, mRevolutionPeriod(0.f)
	, mEccentricity(revolutionObjectParams.eccentricity)
	, mAccumulatedRevolutionTime(0.f)
	, mVelocity(glm::length(revolutionObjectParams.base.initialVelocity))
	, mSemiMajorLength(glm::length(revolutionObjectParams.base.initialPosition)) 
{
	CalcRevolutionPeriod(revolutionObjectParams.centralBodyMu);
	mTrajectoryPts.reserve(360);
}

void RevolutionObject::Revolve(GLfloat delta, GLfloat periodToScale, glm::vec3& nearFociPos) 
{
	float revolutionProportion = mRevolutionPeriod / periodToScale;
	mAccumulatedRevolutionTime += mRevolutionPeriod * delta / (revolutionProportion * EARTH_REVOLUTION_SIMULATION_PERIOD);
	if (mAccumulatedRevolutionTime > mRevolutionPeriod) {
		mAccumulatedRevolutionTime -= mRevolutionPeriod;
	}

	float n = 2.f * glm::pi<float>() / mRevolutionPeriod; // n = mean angular rate
	float M = n * mAccumulatedRevolutionTime; // M (Mean anomaly) = n * t
	float E = CalcEccentricAnomaly(M); // E = Eccentric anomaly
	float theta = 2.f * glm::atan(glm::sqrt((1 + mEccentricity) / (1 - mEccentricity)) * glm::tan(E / 2.f));
	float radius = mSemiMajorLength * (1 - mEccentricity * mEccentricity) / (1 + mEccentricity * glm::cos(theta));
	mCurrentPosition = nearFociPos + glm::rotate(glm::normalize(mInitialPosition), theta, glm::vec3(0.f, 1.f, 0.f)) * radius;
}

float RevolutionObject::GetRevolutionPeriod() const 
{
	return mRevolutionPeriod;
}

void RevolutionObject::CalcTrajectory(glm::vec3& nearFociPos)
{
	mTrajectoryPts.clear();

	float n = 2.f * glm::pi<float>() / mRevolutionPeriod;
	float step = mRevolutionPeriod / 360.f;
	float time = 0.f;
	while (time < mRevolutionPeriod) {
		float M = n * time; // M (Mean anomaly) = n * t
		float E = CalcEccentricAnomaly(M); // E = Eccentric anomaly
		float theta = 2.f * glm::atan(glm::sqrt((1 + mEccentricity) / (1 - mEccentricity)) * glm::tan(E / 2.f));
		float radius = mSemiMajorLength * (1 - mEccentricity * mEccentricity) / (1 + mEccentricity * glm::cos(theta));
		glm::vec3 pt = nearFociPos + glm::rotate(glm::normalize(mInitialPosition), theta, glm::vec3(0.f, 1.f, 0.f)) * radius;
		mTrajectoryPts.push_back(pt);
		time += step;
	}
}

void RevolutionObject::CalcRevolutionPeriod(float centralBodyMu)
{
	mRevolutionPeriod = 2.f * glm::pi<float>() * glm::sqrt(glm::pow(mSemiMajorLength, 3) / centralBodyMu);
}

/// <summary>
/// Calculate Eccentric anomaly by Newton-Raphson method
/// </summary>
/// <param name="meanAnomaly"></param>
/// <returns></returns>
float RevolutionObject::CalcEccentricAnomaly(float meanAnomaly) 
{
	constexpr float TOLERANCE = 1e-4;
	float E = meanAnomaly;
	float deltaE = 1.f;
	while (glm::abs(deltaE) < TOLERANCE) {
		float f = E - mEccentricity * glm::sin(E) - meanAnomaly;
		float df = 1 - mEccentricity * glm::cos(E);
		float deltaE = -f / df;
		E += deltaE;
	}
	return E;
}
