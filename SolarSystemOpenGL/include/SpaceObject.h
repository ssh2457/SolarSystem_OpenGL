#pragma once

#include <spdlog/spdlog.h>

#include <gl/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Model.h"
#include "Common.h"



typedef struct SpaceObjectParams {
	std::string fileName;
	const char* name;
	glm::vec3 initialPosition;
	glm::vec3 initialVelocity;
	float radius;
	float mass;
	float scale;
	float rotationPeriod;
	float inclination;
} spaceObjectParams_t;




class SpaceObject : public Model {
public:
	SpaceObject() = delete;
	SpaceObject(const std::string& fileName, const char* name, 
				glm::vec3& initialPosition, glm::vec3& initialVelocity,
				float radius, float mass,
				float scale, 
				float rotationPeriod,
				float inclination);
	virtual ~SpaceObject();

	const std::string& GetFilePath() const;

	void Update(GLuint uniformWorldLocation, GLfloat delta, GLfloat periodToScale);

	const char* GetName() const;
	float GetMu() const;
	glm::vec3 GetCurrentPosition() const;

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

	glm::vec3 mAxis;
	float mAccumulatedRotationTime;
	float mRotationPeriod;

	glm::mat4 Translate(glm::mat4& model);
	glm::mat4 Rotate(glm::mat4& model, GLfloat delta, GLfloat periodToScale);
	glm::mat4 Scale(glm::mat4& model);
};