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
	sunParams.base.fileName = "../../Models/Sun/Sun.obj";
	sunParams.base.name = "Sun";
	sunParams.base.initialPosition = glm::vec3(0.f, 0.f, 0.f);
	sunParams.base.initialVelocity = glm::vec3(0.f, 0.f, 0.f);
	sunParams.base.radius = 695700.f;
	sunParams.base.mass = 1.98847e30;
	sunParams.base.scale = 4.f;
	sunParams.base.rotationPeriod = 4971364.f;
	sunParams.base.inclination = 0.f; //7.25

	mSun = std::make_unique<Star>(sunParams);
	mSun->LoadModel(mSun->GetFilePath());

	revolutionObjectParams_t earthParams;
	memset(&earthParams, 0, sizeof(revolutionObjectParams_t));
	earthParams.base.fileName = "../../Models/Earth/Earth.obj";
	earthParams.base.name = "Earth";
	earthParams.base.initialPosition = glm::vec3(EARTH_SUN_DISTANCE, 0.f, 0.f);
	earthParams.base.initialVelocity = glm::vec3(0.f, 0.f, -30.29f);
	earthParams.base.radius = 6378.1f;
	earthParams.base.mass = 5.9722e24f;
	earthParams.base.scale = 1.f;
	earthParams.base.rotationPeriod = 86164.f;
	earthParams.base.inclination = glm::radians(23.44f);
	earthParams.eccentricity = 0.0167f;
	earthParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<RevolutionObject>(earthParams));
	mPeriodToScale = mPlanets[0]->GetRevolutionPeriod();

	revolutionObjectParams_t mercuryParams;
	memset(&mercuryParams, 0, sizeof(revolutionObjectParams_t));
	mercuryParams.base.fileName = "../../Models/Mercury/Mercury.obj";
	mercuryParams.base.name = "Mercury";
	mercuryParams.base.initialPosition = glm::vec3(46e6f, 0.f, 0.f);
	mercuryParams.base.initialVelocity = glm::vec3(0.f, 0.f, -58.97f);
	mercuryParams.base.radius = 2440.5f;
	mercuryParams.base.mass = 0.33010e24f;
	mercuryParams.base.scale = 0.383f;
	mercuryParams.base.rotationPeriod = 15201360.f;
	mercuryParams.base.inclination = glm::radians(0.034f);
	mercuryParams.eccentricity = 0.2056;
	mercuryParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<RevolutionObject>(mercuryParams));

	revolutionObjectParams_t venusParams;
	memset(&venusParams, 0, sizeof(revolutionObjectParams_t));
	venusParams.base.fileName = "../../Models/Venus/Venus.obj";
	venusParams.base.name = "Venus";
	venusParams.base.initialPosition = glm::vec3(107.48e6f, 0.f, 0.f);
	venusParams.base.initialVelocity = glm::vec3(0.f, 0.f, -32.26f);
	venusParams.base.radius = 6051.8f;
	venusParams.base.mass = 4.8673e24f;
	venusParams.base.scale = 0.95f;
	venusParams.base.rotationPeriod = 10087200.f;
	venusParams.base.inclination = glm::radians(177.36f);
	venusParams.eccentricity = 0.0068f;
	venusParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<RevolutionObject>(venusParams));



	revolutionObjectParams_t marsParams;
	memset(&marsParams, 0, sizeof(revolutionObjectParams_t));
	marsParams.base.fileName = "../../Models/Mars/Mars.obj";
	marsParams.base.name = "Mars";
	marsParams.base.initialPosition = glm::vec3(206.65e6f, 0.f, 0.f);
	marsParams.base.initialVelocity = glm::vec3(0.f, 0.f, -26.5f);
	marsParams.base.radius = 3396.2f;
	marsParams.base.mass = 0.64169e24f;
	marsParams.base.scale = 0.532f;
	marsParams.base.rotationPeriod = 88642.44f;
	marsParams.base.inclination = glm::radians(25.19f);
	marsParams.eccentricity = 0.0935f;
	marsParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<RevolutionObject>(marsParams));

	revolutionObjectParams_t jupiterParams;
	memset(&jupiterParams, 0, sizeof(revolutionObjectParams_t));
	jupiterParams.base.fileName = "../../Models/Jupiter/Jupiter.obj";
	jupiterParams.base.name = "Jupiter";
	jupiterParams.base.initialPosition = glm::vec3(740.595e6f, 0.f, 0.f);
	jupiterParams.base.initialVelocity = glm::vec3(0.f, 0.f, -13.72f);
	jupiterParams.base.radius = 71492.f;
	jupiterParams.base.mass = 1898.13e24f;
	jupiterParams.base.scale = 3.0f;
	jupiterParams.base.rotationPeriod = 35733.24f;
	jupiterParams.base.inclination = glm::radians(3.13f);
	jupiterParams.eccentricity = 0.0487f;
	jupiterParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<RevolutionObject>(jupiterParams));

	revolutionObjectParams_t saturnParams;
	memset(&saturnParams, 0, sizeof(revolutionObjectParams_t));
	saturnParams.base.fileName = "../../Models/Saturn/Saturn.obj";
	saturnParams.base.name = "Saturn";
	saturnParams.base.initialPosition = glm::vec3(1357.554e6f, 0.f, 0.f);
	saturnParams.base.initialVelocity = glm::vec3(0.f, 0.f, -10.14f);
	saturnParams.base.radius = 58232.f;
	saturnParams.base.mass = 568.32e24f;
	saturnParams.base.scale = 1.7f;
	saturnParams.base.rotationPeriod = 38361.6f;
	saturnParams.base.inclination = glm::radians(26.73f);
	saturnParams.eccentricity = 0.0520f;
	saturnParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<RevolutionObject>(saturnParams));

	revolutionObjectParams_t uranosParams;
	memset(&uranosParams, 0, sizeof(revolutionObjectParams_t));
	uranosParams.base.fileName = "../../Models/Uranos/Uranos.obj";
	uranosParams.base.name = "Uranos";
	uranosParams.base.initialPosition = glm::vec3(2732.696e6f, 0.f, 0.f);
	uranosParams.base.initialVelocity = glm::vec3(0.f, 0.f, -7.13f);
	uranosParams.base.radius = 25362.f;
	uranosParams.base.mass = 86.811e24f;
	uranosParams.base.scale = 1.4f;
	uranosParams.base.rotationPeriod = 62064.f;
	uranosParams.base.inclination = glm::radians(97.77f);
	uranosParams.eccentricity = 0.0469f;
	uranosParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<RevolutionObject>(uranosParams));

	revolutionObjectParams_t neptuneParams;
	memset(&neptuneParams, 0, sizeof(revolutionObjectParams_t));
	neptuneParams.base.fileName = "../../Models/Neptune/Neptune.obj";
	neptuneParams.base.name = "Neptune";
	neptuneParams.base.initialPosition = glm::vec3(4471.05e6f, 0.f, 0.f);
	neptuneParams.base.initialVelocity = glm::vec3(0.f, 0.f, -5.47f);
	neptuneParams.base.radius = 24622.f;
	neptuneParams.base.mass = 102.409e24f;
	neptuneParams.base.scale = 1.5f;
	neptuneParams.base.rotationPeriod = 57996.f;
	neptuneParams.base.inclination = glm::radians(23.32f);
	neptuneParams.eccentricity = 0.0097f;
	neptuneParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<RevolutionObject>(neptuneParams));


	revolutionObjectParams_t moonParams;
	memset(&moonParams, 0, sizeof(revolutionObjectParams_t));
	moonParams.base.fileName = "../../Models/Moon/Moon.obj";
	moonParams.base.name = "Moon";
	moonParams.base.initialPosition = glm::vec3(0.3633e6f, 0.f, 0.f);
	moonParams.base.initialVelocity = glm::vec3(0.f, 0.f, -1.082);
	moonParams.base.radius = 1738.1;
	moonParams.base.mass = 0.07346e24f;
	moonParams.base.scale = 0.2725f;
	moonParams.base.rotationPeriod = 2360592.f;
	moonParams.base.inclination = glm::radians(5.145f);
	moonParams.eccentricity = 0.0549f;
	moonParams.centralBodyMu = mPlanets[0]->GetMu();

	mPlanets.push_back(std::make_unique<RevolutionObject>(moonParams));


	for (auto& planet : mPlanets) {
		planet->LoadModel(planet->GetFilePath());
	}
}

void SolarSystem::Tick(Shader* shader, GLuint uniformWorldLocation, GLfloat delta) {
	shader->SetPointLight(mSun->GetPointLight());
	//mSun->Update(uniformWorldLocation, delta, mPeriodToScale);
	//mSun->RenderModel();

	for (auto& planet : mPlanets) {
		if (std::string(planet->GetName()) == "Moon") {
			planet->Revolve(mPlanets[0]->GetMu(), delta, mPeriodToScale, mPlanets[0]->GetCurrentPosition());
		}
		else {
			planet->Revolve(mSun->GetMu(), delta, mPeriodToScale, mSun->GetCurrentPosition());
		}
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



Star* SolarSystem::GetSun() const {
	return mSun.get();
}

GLfloat SolarSystem::GetPeriodToScale() const
{
	return mPeriodToScale;
}
