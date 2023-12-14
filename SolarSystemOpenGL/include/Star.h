#pragma once

#include "SpaceObject.h"
#include "PointLight.h"

typedef struct StarParams {
	spaceObjectParams_t base;
} starParams_t;

class Star : public SpaceObject {
public:
	Star() = delete;
	Star(starParams_t& starParams);
	virtual ~Star() = default;

	void Light();
private:
	std::unique_ptr<PointLight> mPointLight;
};
