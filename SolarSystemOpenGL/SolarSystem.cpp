#include "include/SolarSystem.h"

std::unique_ptr<SolarSystem> SolarSystem::instance = nullptr;

std::unique_ptr<SolarSystem> SolarSystem::GetInstance() {
	if (instance) {
		return std::move(instance);
	}
	instance = std::make_unique<SolarSystem>();
	SPDLOG_INFO("A solar system instance is created");
	return std::move(instance);
}

void SolarSystem::LoadSolarSystem() {
	mSun = std::make_unique<Star>("../../Models/Sun/Sun.obj", "Sun", 
									glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f),
									695700.f, 1.98847e30,
									4.f, 
									4971364.f);
	mSun->LoadModel(mSun->GetFilePath());

	mPlanets.push_back(std::make_unique<RevolutionObject>("../../Models/Earth/Earth.obj", "Earth",
												glm::vec3(EARTH_SUN_DISTANCE, 0.f, 0.f), glm::vec3(0.f, 0.f, -30.29f),
												6378.1f, 5.9722e24f,
												1.f, 
												86164.f,
												0.0167f,
												mSun->GetMu()));
	mPeriodToScale = mPlanets[0]->GetRevolutionPeriod();

	mPlanets.push_back(std::make_unique<RevolutionObject>("../../Models/Mercury/Mercury.obj", "Mercury",
												glm::vec3(46e6f, 0.f, 0.f), glm::vec3(0.f, 0.f, -58.97f),
												2440.5f, 0.33010e24f,
												0.383f,
												15201360.f,
												0.2056,
												mSun->GetMu()));

	mPlanets.push_back(std::make_unique<RevolutionObject>("../../Models/Venus/Venus.obj", "Venus",
												glm::vec3(107.48e6f, 0.f, 0.f), glm::vec3(0.f, 0.f, -32.26f),
												6051.8f, 4.8673e24f,
												0.95f,
												10087200.f,
												0.0068f,
												mSun->GetMu()));

	mPlanets.push_back(std::make_unique<RevolutionObject>("../../Models/Mars/Mars.obj", "Mars",
												glm::vec3(206.65e6f, 0.f, 0.f), glm::vec3(0.f, 0.f, -26.5f),
												3396.2f, 0.64169e24f,
												0.532f,
												88642.44f,
												0.0935f,
												mSun->GetMu()));

	mPlanets.push_back(std::make_unique<RevolutionObject>("../../Models/Jupiter/Jupiter.obj", "Jupiter",
												glm::vec3(740.595e6f, 0.f, 0.f), glm::vec3(0.f, 0.f, -13.72f),
												71492.f, 1898.13e24f,
												3.0f,
												35733.24f,
												0.0487f,
												mSun->GetMu()));

	for (auto& planet : mPlanets) {
		planet->LoadModel(planet->GetFilePath());
	}
}

void SolarSystem::Tick(GLuint uniformWorldLocation, GLfloat delta) {
	mSun->Update(uniformWorldLocation, delta, mPeriodToScale);
	mSun->RenderModel();

	for (auto& planet : mPlanets) {
		planet->Revolve(mSun->GetMu(), delta, mPeriodToScale);
		planet->Update(uniformWorldLocation, delta, mPeriodToScale);
		planet->RenderModel();
	}
}

SolarSystem::~SolarSystem() {
	mSun = nullptr;
	for (auto& planet : mPlanets) {
		planet = nullptr;
	}
}
