#pragma once

#include "SpaceObject.h"

class Planet : public SpaceObject {
public:
	Planet() = delete;
	Planet(const std::string& fileName, const char* name, glm::vec3& position, float scale, float rotationSpeed, float revolutionSpeed);
	virtual ~Planet() = default;

	void Revolve();
private:
	float mRevolutionSpeed;
};