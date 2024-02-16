#pragma once

#include "CelestialBody.h"
#include "PointLight.h"

typedef struct StarParams {
	celestialBodyParams_t base;
} starParams_t;

class Star : public CelestialBody {
public:
	Star() = delete;
	Star(starParams_t& starParams);
	virtual ~Star() = default;
private:
};