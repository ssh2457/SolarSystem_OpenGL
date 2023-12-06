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
	mSun = std::make_unique<Star>("../../Models/Sun/Sun.obj", "Sun", glm::vec3(0.f, 0.f, 0.f), 5.f, 10.f);
	mSun->LoadModel(mSun->GetFilePath());

	mPlanets.push_back(std::make_unique<Planet>("../../Models/Earth/Earth.obj", "Earth", glm::vec3(20.f, 0.f, 0.f), 1.f, 1.f, 1.f));

	for (auto& planet : mPlanets) {
		planet->LoadModel(planet->GetFilePath());
	}
}

void SolarSystem::Tick(GLuint uniformWorldLocation, float time) {
	mSun->Update(uniformWorldLocation, time);

	mSun->RenderModel();
	for (auto& planet : mPlanets) {
		planet->Update(uniformWorldLocation, time);
		planet->RenderModel();
	}
}

SolarSystem::~SolarSystem() {
	mSun = nullptr;
	for (auto& planet : mPlanets) {
		planet = nullptr;
	}
}