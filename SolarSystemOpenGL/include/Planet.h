#pragma once

#include <glm/gtx/rotate_vector.hpp>

#include "RevolutionableBody.h"
#include "Satellite.h"

#include <vector>


class Planet : public RevolutionableBody {
public:
	Planet() = delete;
	Planet(revolutionableBodyParams_t& planetParams);
	virtual ~Planet() = default;

	void AddSatellite(std::unique_ptr<Satellite> satellite);
	void LoadSatelliteModels();
	void UpdateSatellites(GLuint uniformWorldLocation, GLfloat delta, GLfloat periodToScale, Planet* governingPlanet);
private:
	std::vector<std::unique_ptr<Satellite>> satellites;
};
