#pragma once

#include <spdlog/spdlog.h>

#include <gl/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Model.h"
#include "Common.h"

class SpaceObject : public Model {
public:
	SpaceObject() = delete;
	SpaceObject(const std::string& fileName, const char* name, 
				glm::vec3& initialPosition, glm::vec3& initialVelocity,
				float radius, float mass,
				float scale, 
				float rotationPeriod);
	virtual ~SpaceObject();

	const std::string& GetFilePath() const;

	void Update(GLuint uniformWorldLocation, GLfloat time);

	float GetMu() const;

protected:
	const std::string mFileName;
	char* mName;
	//std::unique_ptr<char> mName;
	glm::vec3 mInitialPosition;
	glm::vec3 mCurrentPosition;
	glm::vec3 mInitialVelocity;
	float mScale;
	float mRadius;
	float mMass;
	const float mGravitionalConstant;
	float mMu;

	glm::vec3 mAxis;
	float mRotationAngle;
	float mRotationPeriod;

	glm::mat4 Translate(glm::mat4 model);
	glm::mat4 Rotate(glm::mat4 model, GLfloat time);
	glm::mat4 Scale(glm::mat4 model);
};