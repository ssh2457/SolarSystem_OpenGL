#pragma once

#include "SpaceObject.h"

class Star : public SpaceObject {
public:
	Star() = delete;
	Star(const std::string& fileName, const char* name, glm::vec3& position, float scale, float rotationSpeed);
	virtual ~Star() = default;
private:
};