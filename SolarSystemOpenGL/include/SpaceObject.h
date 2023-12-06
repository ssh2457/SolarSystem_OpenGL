#pragma once

#include <spdlog/spdlog.h>

#include <gl/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Model.h"

class SpaceObject : public Model {
public:
	SpaceObject() = delete;
	SpaceObject(const std::string& fileName, const char* name, glm::vec3& position, float scale, float rotationSpeed);
	virtual ~SpaceObject();

	const std::string& GetFilePath() const;

	void Update(GLuint uniformWorldLocation, float time);


protected:
	const std::string mFileName;
	char* mName;
	//std::unique_ptr<char> mName;
	glm::vec3 mPosition;
	float mScale;

	glm::vec3 mAxis;
	float mRotationAngle;
	float mRotationSpeed;

	glm::mat4 Translate(glm::mat4 model);
	glm::mat4 Rotate(glm::mat4 model, float time);
	glm::mat4 Scale(glm::mat4 model);
};