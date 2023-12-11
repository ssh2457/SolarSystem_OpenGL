#pragma once

#include <spdlog/spdlog.h>

#include<memory>
#include <vector>

#include "Common.h"
#include "Star.h"
#include "RevolutionObject.h"
#include "Model.h"

class SolarSystem {
	friend std::unique_ptr<SolarSystem> std::make_unique<SolarSystem>();
	friend std::unique_ptr<SolarSystem>::deleter_type;
public:
	SolarSystem(const SolarSystem& ) = delete;
	SolarSystem& operator=(const SolarSystem&) = delete;
	
	static std::unique_ptr<SolarSystem> GetInstance();

	void LoadSolarSystem();
	void Tick(GLuint uniformWorldLocation, GLfloat delta);
private:
	SolarSystem() = default;
	virtual ~SolarSystem();

	static std::unique_ptr<SolarSystem> instance;

	std::unique_ptr<Star> mSun;
	std::vector<std::unique_ptr<RevolutionObject>> mPlanets;

	GLfloat mPeriodToScale;
};