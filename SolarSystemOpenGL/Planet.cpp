#include "include/Planet.h"

Planet::Planet(const std::string& fileName, const char* name, glm::vec3& position, float scale, float rotationSpeed, float revolutionSpeed)
	: SpaceObject(fileName, name, position, scale, rotationSpeed)
	, mRevolutionSpeed(revolutionSpeed) {
}

void Planet::Revolve() {

}
