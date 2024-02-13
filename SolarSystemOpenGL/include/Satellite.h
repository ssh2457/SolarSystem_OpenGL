#pragma once

#include <glm/gtx/rotate_vector.hpp>

#include "RevolutionableBody.h"

#include <vector>


class Satellite : public RevolutionableBody {
public:
	Satellite() = delete;
	Satellite(revolutionableBodyParams_t& satelliteParams);
	virtual ~Satellite() = default;

private:
};