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
	starParams_t sunParams;
	memset(&sunParams, 0, sizeof(starParams_t));
	sunParams.base.fileName = "../../../../Blender models/Sun/Sun.obj";
	sunParams.base.name = "Sun";
	sunParams.base.initialPosition = glm::vec3(0.f, 0.f, 0.f);
	sunParams.base.initialVelocity = glm::vec3(0.f, 0.f, 0.f);
	sunParams.base.radius = 695700.f;
	sunParams.base.mass = 1.98847e30;
	sunParams.base.scale = 3.25f;
	sunParams.base.rotationPeriod = 4971364.f;
	sunParams.base.inclination = 0.f; //7.25
	sunParams.base.simulationInitialDistance = 0.f;

	mSun = std::make_unique<Star>(sunParams);
	mSun->LoadModel(mSun->GetFilePath());

	planetParams_t earthParams;
	memset(&earthParams, 0, sizeof(planetParams_t));
	earthParams.base.base.fileName = "../../../../Blender models/Earth/Earth.obj";
	earthParams.base.base.name = "Earth";
	earthParams.base.base.initialPosition = glm::vec3(EARTH_SUN_DISTANCE, 0.f, 0.f);
	earthParams.base.base.initialVelocity = glm::vec3(0.f, 0.f, -30.29f);
	earthParams.base.base.radius = 6378.1f;
	earthParams.base.base.mass = 5.9722e24f;
	earthParams.base.base.scale = 0.5f;
	earthParams.base.base.rotationPeriod = 86164.f;
	earthParams.base.base.inclination = glm::radians(23.44f);
	earthParams.base.base.simulationInitialDistance = 15.f;
	earthParams.base.eccentricity = 0.0167f;
	earthParams.base.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(earthParams));
	mPeriodToScale = mPlanets[0]->GetRevolutionPeriod();

	satelliteParams_t moonParams;
	memset(&moonParams, 0, sizeof(planetParams_t));
	moonParams.base.fileName = "../../../../Blender models/Moon/Moon.obj";
	moonParams.base.name = "Moon";
	moonParams.base.initialPosition = glm::vec3(glm::length(earthParams.base.base.initialPosition) + 0.3633e6f, 0.f, 0.f);
	moonParams.base.initialVelocity = glm::vec3(0.f, 0.f, -1.082);
	moonParams.base.radius = 1738.1;
	moonParams.base.mass = 0.07346e24f;
	moonParams.base.scale = 0.11f;
	moonParams.base.rotationPeriod = 2360592.f;
	moonParams.base.inclination = glm::radians(5.145f);
	moonParams.base.simulationInitialDistance = 5.f;
	moonParams.eccentricity = 0.0549f;
	moonParams.centralBodyMu = mPlanets[0]->GetMu();

	mPlanets[0]->AddSatellite(moonParams);

	planetParams_t mercuryParams;
	memset(&mercuryParams, 0, sizeof(planetParams_t));
	mercuryParams.base.base.fileName = "../../../../Blender models/Mercury/Mercury.obj";
	mercuryParams.base.base.name = "Mercury";
	mercuryParams.base.base.initialPosition = glm::vec3(46e6f, 0.f, 0.f);
	mercuryParams.base.base.initialVelocity = glm::vec3(0.f, 0.f, -58.97f);
	mercuryParams.base.base.radius = 2440.5f;
	mercuryParams.base.base.mass = 0.33010e24f;
	mercuryParams.base.base.rotationPeriod = 15201360.f;
	mercuryParams.base.base.inclination = glm::radians(0.034f);
	mercuryParams.base.base.scale = 0.17;
	mercuryParams.base.base.simulationInitialDistance = 5.f;
	mercuryParams.base.eccentricity = 0.2056;
	mercuryParams.base.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(mercuryParams));

	planetParams_t venusParams;
	memset(&venusParams, 0, sizeof(planetParams_t));
	venusParams.base.base.fileName = "../../../../Blender models/Venus/Venus.obj";
	venusParams.base.base.name = "Venus";
	venusParams.base.base.initialPosition = glm::vec3(107.48e6f, 0.f, 0.f);
	venusParams.base.base.initialVelocity = glm::vec3(0.f, 0.f, -32.26f);
	venusParams.base.base.radius = 6051.8f;
	venusParams.base.base.mass = 4.8673e24f;
	venusParams.base.base.scale = 0.43f;
	venusParams.base.base.rotationPeriod = 10087200.f;
	venusParams.base.base.inclination = glm::radians(177.36f);
	venusParams.base.base.simulationInitialDistance = 10.f;
	venusParams.base.eccentricity = 0.0068f;
	venusParams.base.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(venusParams));



	planetParams_t marsParams;
	memset(&marsParams, 0, sizeof(planetParams_t));
	marsParams.base.base.fileName = "../../../../Blender models/Mars/Mars.obj";
	marsParams.base.base.name = "Mars";
	marsParams.base.base.initialPosition = glm::vec3(206.65e6f, 0.f, 0.f);
	marsParams.base.base.initialVelocity = glm::vec3(0.f, 0.f, -26.5f);
	marsParams.base.base.radius = 3396.2f;
	marsParams.base.base.mass = 0.64169e24f;
	marsParams.base.base.scale = 0.26f;
	marsParams.base.base.rotationPeriod = 88642.44f;
	marsParams.base.base.inclination = glm::radians(25.19f);
	marsParams.base.base.simulationInitialDistance = 20.f;
	marsParams.base.eccentricity = 0.0935f;
	marsParams.base.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(marsParams));

	planetParams_t jupiterParams;
	memset(&jupiterParams, 0, sizeof(planetParams_t));
	jupiterParams.base.base.fileName = "../../../../Blender models/Jupiter/Jupiter.obj";
	jupiterParams.base.base.name = "Jupiter";
	jupiterParams.base.base.initialPosition = glm::vec3(740.595e6f, 0.f, 0.f);
	jupiterParams.base.base.initialVelocity = glm::vec3(0.f, 0.f, -13.72f);
	jupiterParams.base.base.radius = 71492.f;
	jupiterParams.base.base.mass = 1898.13e24f;
	jupiterParams.base.base.scale = 1.5f;
	jupiterParams.base.base.rotationPeriod = 35733.24f;
	jupiterParams.base.base.inclination = glm::radians(3.13f);
	jupiterParams.base.base.simulationInitialDistance = 30.f;
	jupiterParams.base.eccentricity = 0.0487f;
	jupiterParams.base.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(jupiterParams));

	planetParams_t saturnParams;
	memset(&saturnParams, 0, sizeof(planetParams_t));
	saturnParams.base.base.fileName = "../../../../Blender models/Saturn/Saturn.obj";
	saturnParams.base.base.name = "Saturn";
	saturnParams.base.base.initialPosition = glm::vec3(1357.554e6f, 0.f, 0.f);
	saturnParams.base.base.initialVelocity = glm::vec3(0.f, 0.f, -10.14f);
	saturnParams.base.base.radius = 58232.f;
	saturnParams.base.base.mass = 568.32e24f;
	saturnParams.base.base.scale = 1.3f;
	saturnParams.base.base.rotationPeriod = 38361.6f;
	saturnParams.base.base.inclination = glm::radians(26.73f);
	saturnParams.base.base.simulationInitialDistance = 40.f;
	saturnParams.base.eccentricity = 0.0520f;
	saturnParams.base.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(saturnParams));

	planetParams_t uranosParams;
	memset(&uranosParams, 0, sizeof(planetParams_t));
	uranosParams.base.base.fileName = "../../../../Blender models/Uranos/Uranos.obj";
	uranosParams.base.base.name = "Uranos";
	uranosParams.base.base.initialPosition = glm::vec3(2732.696e6f, 0.f, 0.f);
	uranosParams.base.base.initialVelocity = glm::vec3(0.f, 0.f, -7.13f);
	uranosParams.base.base.radius = 25362.f;
	uranosParams.base.base.mass = 86.811e24f;
	uranosParams.base.base.scale = 1.35f;
	uranosParams.base.base.rotationPeriod = 62064.f;
	uranosParams.base.base.inclination = glm::radians(97.77f);
	uranosParams.base.base.simulationInitialDistance = 50.f;
	uranosParams.base.eccentricity = 0.0469f;
	uranosParams.base.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(uranosParams));

	planetParams_t neptuneParams;
	memset(&neptuneParams, 0, sizeof(planetParams_t));
	neptuneParams.base.base.fileName = "../../../../Blender models/Neptune/Neptune.obj";
	neptuneParams.base.base.name = "Neptune";
	neptuneParams.base.base.initialPosition = glm::vec3(4471.05e6f, 0.f, 0.f);
	neptuneParams.base.base.initialVelocity = glm::vec3(0.f, 0.f, -5.47f);
	neptuneParams.base.base.radius = 24622.f;
	neptuneParams.base.base.mass = 102.409e24f;
	neptuneParams.base.base.scale = 1.3f;
	neptuneParams.base.base.rotationPeriod = 57996.f;
	neptuneParams.base.base.inclination = glm::radians(23.32f);
	neptuneParams.base.base.simulationInitialDistance = 60.f;
	neptuneParams.base.eccentricity = 0.0097f;
	neptuneParams.base.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(neptuneParams));
	

	for (auto& planet : mPlanets) {
		planet->LoadModel(planet->GetFilePath());
		planet->LoadSatelliteModels();
	}
}

void SolarSystem::UpdateSun(GLuint uniformWorld, GLfloat delta) {
	mSun->Update(uniformWorld, delta, mPeriodToScale);
	mSun->RenderModel();
}

void SolarSystem::UpdatePlanets(GLuint uniformWorldLocation, GLfloat delta) {
	for (auto& planet : mPlanets) {
		planet->Revolve(delta, mPeriodToScale, mSun->GetCurrentPosition());
		planet->Update(uniformWorldLocation, delta, mPeriodToScale);
		planet->RenderModel();

		planet->UpdateSatellites(uniformWorldLocation, delta, mPeriodToScale);
	}
}


SolarSystem::~SolarSystem() {
	mSun = nullptr;
	for (auto& planet : mPlanets) {
		planet = nullptr;
	}
}



Star* SolarSystem::GetSun() const {
	return mSun.get();
}

GLfloat SolarSystem::GetPeriodToScale() const
{
	return mPeriodToScale;
}
