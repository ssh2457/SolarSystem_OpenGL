#include "include/Star.h"

Star::Star(const std::string& fileName, const char* name,
			glm::vec3& position, glm::vec3& velocity,
			float radius, float mass,
			float scale,
			float rotationPeriod)
	: SpaceObject(fileName, name, position, velocity, radius, mass, scale, rotationPeriod) {
}

void Star::Light() {

}

