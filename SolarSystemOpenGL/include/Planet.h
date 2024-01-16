#pragma once

#include <glm/gtx/rotate_vector.hpp>

#include "CelestialBody.h"
#include "Satellite.h"

#include <vector>

typedef struct PlanetParams {
	satelliteParams_t base;
} planetParams_t;

class Planet : public Satellite {
public:
	Planet() = delete;
	Planet(planetParams_t& planetParams);
	virtual ~Planet() = default;

	void AddSatellite(satelliteParams_t& satellite);
	void LoadSatelliteModels();
	void UpdateSatellites(GLuint uniformWorldLocation, GLfloat delta, GLfloat periodToScale);
private:
	std::vector<std::unique_ptr<Satellite>> satellites;
};
