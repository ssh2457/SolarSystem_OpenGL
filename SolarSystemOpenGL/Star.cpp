#include "include/Star.h"

Star::Star(const std::string& fileName, const char* name, glm::vec3& position, float scale, float rotationSpeed)
	: SpaceObject(fileName, name, position, scale, rotationSpeed) {
}
