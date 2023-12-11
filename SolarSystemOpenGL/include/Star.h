#pragma once

#include "SpaceObject.h"

class Star : public SpaceObject {
public:
	Star() = delete;
	Star(const std::string& fileName, const char* name, 
		glm::vec3& position, glm::vec3& velocity,
		float radius, float mass,
		float scale, 
		float rotationPeriod);
	virtual ~Star() = default;

	void Light();
private:
};
