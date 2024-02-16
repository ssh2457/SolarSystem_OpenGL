#pragma once

#include <spdlog/spdlog.h>

#include<memory>
#include <vector>

#include "Common.h"
#include "Star.h"
#include "Planet.h"
#include "Satellite.h"
#include "Model.h"

#include "Shader.h"

class SolarSystem {
	friend std::unique_ptr<SolarSystem> std::make_unique<SolarSystem>();
	friend std::unique_ptr<SolarSystem>::deleter_type;
public:
	SolarSystem(const SolarSystem& other) = delete;
	SolarSystem& operator=(const SolarSystem& other) = delete;
	
	static std::unique_ptr<SolarSystem> GetInstance();

	void LoadSolarSystem();
	void UpdateSun(GLuint uniformWorld, GLfloat delta);
	void UpdatePlanets(GLuint uniformWorldLocation, GLfloat delta);


	// TEST FUNCTIONS
	Star* GetSun() const;
	GLfloat GetPeriodToScale() const;
private:
	SolarSystem() = default;
	virtual ~SolarSystem();

	static std::unique_ptr<SolarSystem> instance;

	std::unique_ptr<Star> mSun;
	std::vector<std::unique_ptr<Planet>> mPlanets;

	GLfloat mPeriodToScale;
};