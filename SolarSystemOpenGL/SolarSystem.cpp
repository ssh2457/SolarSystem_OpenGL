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

	revolutionableBodyParams_t earthParams;
	memset(&earthParams, 0, sizeof(revolutionableBodyParams_t));
	earthParams.base.fileName = "../../../../Blender models/Earth/Earth.obj";
	earthParams.base.name = "Earth";
	earthParams.base.initialPosition = glm::vec3(EARTH_SUN_DISTANCE, 0.f, 0.f);
	earthParams.base.initialVelocity = glm::vec3(0.f, 0.f, -30.29f);
	earthParams.base.radius = 6378.1f;
	earthParams.base.mass = 5.9722e24f;
	earthParams.base.scale = 0.5f;
	earthParams.base.rotationPeriod = 86164.f;
	earthParams.base.inclination = glm::radians(23.44f);
	earthParams.base.simulationInitialDistance = 15.f;
	earthParams.eccentricity = 0.0167f;
	earthParams.semiMajorLength = EARTH_SUN_DISTANCE;
	earthParams.centralBodyMu = mSun->GetMu();

	std::unique_ptr<Planet> earth = std::make_unique<Planet>(earthParams);
	mPeriodToScale = earth->GetRevolutionPeriod();


	revolutionableBodyParams_t moonParams;
	memset(&moonParams, 0, sizeof(revolutionableBodyParams_t));
	moonParams.base.fileName = "../../../../Blender models/Moon/Moon.obj";
	moonParams.base.name = "Moon";
	moonParams.base.initialPosition = glm::vec3(glm::length(earthParams.base.initialPosition) + 0.3633e6f, 0.f, 0.f);
	moonParams.base.initialVelocity = glm::vec3(0.f, 0.f, -1.082);
	moonParams.base.radius = 1738.1;
	moonParams.base.mass = 0.07346e24f;
	moonParams.base.scale = 0.11f;
	moonParams.base.rotationPeriod = 2360592.f;
	moonParams.base.inclination = glm::radians(5.145f);
	moonParams.base.simulationInitialDistance = earthParams.base.simulationInitialDistance + 1.5f;
	moonParams.eccentricity = 0.0549f;
	moonParams.semiMajorLength = 0.3633e6f;
	moonParams.centralBodyMu = earth->GetMu();

	earth->AddSatellite(std::make_unique<Satellite>(moonParams));
	mPlanets.push_back(std::move(earth));
	

	revolutionableBodyParams_t mercuryParams;
	memset(&mercuryParams, 0, sizeof(revolutionableBodyParams_t));
	mercuryParams.base.fileName = "../../../../Blender models/Mercury/Mercury.obj";
	mercuryParams.base.name = "Mercury";
	mercuryParams.base.initialPosition = glm::vec3(46e6f, 0.f, 0.f);
	mercuryParams.base.initialVelocity = glm::vec3(0.f, 0.f, -58.97f);
	mercuryParams.base.radius = 2440.5f;
	mercuryParams.base.mass = 0.33010e24f;
	mercuryParams.base.rotationPeriod = 15201360.f;
	mercuryParams.base.inclination = glm::radians(0.034f);
	mercuryParams.base.scale = 0.17;
	mercuryParams.base.simulationInitialDistance = 5.f;
	mercuryParams.eccentricity = 0.2056;
	mercuryParams.semiMajorLength = 46e6f;
	mercuryParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(mercuryParams));

	revolutionableBodyParams_t venusParams;
	memset(&venusParams, 0, sizeof(revolutionableBodyParams_t));
	venusParams.base.fileName = "../../../../Blender models/Venus/Venus.obj";
	venusParams.base.name = "Venus";
	venusParams.base.initialPosition = glm::vec3(107.48e6f, 0.f, 0.f);
	venusParams.base.initialVelocity = glm::vec3(0.f, 0.f, -32.26f);
	venusParams.base.radius = 6051.8f;
	venusParams.base.mass = 4.8673e24f;
	venusParams.base.scale = 0.43f;
	venusParams.base.rotationPeriod = 10087200.f;
	venusParams.base.inclination = glm::radians(177.36f);
	venusParams.base.simulationInitialDistance = 10.f;
	venusParams.eccentricity = 0.0068f;
	venusParams.semiMajorLength = 107.48e6f;
	venusParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(venusParams));



	revolutionableBodyParams_t marsParams;
	memset(&marsParams, 0, sizeof(revolutionableBodyParams_t));
	marsParams.base.fileName = "../../../../Blender models/Mars/Mars.obj";
	marsParams.base.name = "Mars";
	marsParams.base.initialPosition = glm::vec3(206.65e6f, 0.f, 0.f);
	marsParams.base.initialVelocity = glm::vec3(0.f, 0.f, -26.5f);
	marsParams.base.radius = 3396.2f;
	marsParams.base.mass = 0.64169e24f;
	marsParams.base.scale = 0.26f;
	marsParams.base.rotationPeriod = 88642.44f;
	marsParams.base.inclination = glm::radians(25.19f);
	marsParams.base.simulationInitialDistance = 20.f;
	marsParams.eccentricity = 0.0935f;
	marsParams.semiMajorLength = 206.65e6f;
	marsParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(marsParams));

	revolutionableBodyParams_t jupiterParams;
	memset(&jupiterParams, 0, sizeof(revolutionableBodyParams_t));
	jupiterParams.base.fileName = "../../../../Blender models/Jupiter/Jupiter.obj";
	jupiterParams.base.name = "Jupiter";
	jupiterParams.base.initialPosition = glm::vec3(740.595e6f, 0.f, 0.f);
	jupiterParams.base.initialVelocity = glm::vec3(0.f, 0.f, -13.72f);
	jupiterParams.base.radius = 71492.f;
	jupiterParams.base.mass = 1898.13e24f;
	jupiterParams.base.scale = 1.5f;
	jupiterParams.base.rotationPeriod = 35733.24f;
	jupiterParams.base.inclination = glm::radians(3.13f);
	jupiterParams.base.simulationInitialDistance = 30.f;
	jupiterParams.eccentricity = 0.0487f;
	jupiterParams.semiMajorLength = 740.595e6f;
	jupiterParams.centralBodyMu = mSun->GetMu();

	std::unique_ptr<Planet> jupiter = std::make_unique<Planet>(jupiterParams);

	
	revolutionableBodyParams_t europaParams;
	memset(&europaParams, 0, sizeof(revolutionableBodyParams_t));
	europaParams.base.fileName = "../../../../Blender models/Europa/Europa.obj";
	europaParams.base.name = "Europa";
	europaParams.base.initialPosition = glm::vec3(glm::length(jupiterParams.base.initialPosition) + 0.664862e6f, 0.f, 0.f);
	europaParams.base.initialVelocity = glm::vec3(0.f, 0.f, -13.743);
	europaParams.base.radius = 1560.8;
	europaParams.base.mass = 0.04799844e24f;
	europaParams.base.scale = 0.10f;
	europaParams.base.rotationPeriod = 302400.f;
	europaParams.base.inclination = glm::radians(0.47f + jupiterParams.base.inclination);
	europaParams.base.simulationInitialDistance = jupiterParams.base.simulationInitialDistance + 2.5f; //
	europaParams.eccentricity = 0.009f;
	europaParams.semiMajorLength = 0.6709e6f;
	europaParams.centralBodyMu = jupiter->GetMu();

	jupiter->AddSatellite(std::make_unique<Satellite>(europaParams));

	
	revolutionableBodyParams_t ganymedeParams;
	memset(&ganymedeParams, 0, sizeof(revolutionableBodyParams_t));
	ganymedeParams.base.fileName = "../../../../Blender models/Ganymede/Ganymede.obj";
	ganymedeParams.base.name = "Ganymede";
	ganymedeParams.base.initialPosition = glm::vec3(glm::length(jupiterParams.base.initialPosition) + 1.069200e6f, 0.f, 0.f);
	ganymedeParams.base.initialVelocity = glm::vec3(0.f, 0.f, -10.880);
	ganymedeParams.base.radius = 2634.1f;
	ganymedeParams.base.mass = 0.14819e24f;
	ganymedeParams.base.scale = 0.17f;
	ganymedeParams.base.rotationPeriod = 618153.3792f;
	ganymedeParams.base.inclination = glm::radians(jupiterParams.base.inclination);
	ganymedeParams.base.simulationInitialDistance = jupiterParams.base.simulationInitialDistance + 3.5f; //
	ganymedeParams.eccentricity = 0.0013f;
	ganymedeParams.semiMajorLength = 1.0704e6f;
	ganymedeParams.centralBodyMu = jupiter->GetMu();

	jupiter->AddSatellite(std::make_unique<Satellite>(ganymedeParams));
	

	
	revolutionableBodyParams_t ioParams;
	memset(&ioParams, 0, sizeof(revolutionableBodyParams_t));
	ioParams.base.fileName = "../../../../Blender models/IO/IO.obj";
	ioParams.base.name = "IO";
	ioParams.base.initialPosition = glm::vec3(glm::length(jupiterParams.base.initialPosition) + 0.42e6f, 0.f, 0.f);
	ioParams.base.initialVelocity = glm::vec3(0.f, 0.f, -17.334);
	ioParams.base.radius = 1821.6f;
	ioParams.base.mass = 0.08931938e24f;
	ioParams.base.scale = 0.12f; 
	ioParams.base.rotationPeriod = 152853.5047f;
	ioParams.base.inclination = glm::radians(jupiterParams.base.inclination + 0.63f);
	ioParams.base.simulationInitialDistance = jupiterParams.base.simulationInitialDistance + 1.85f; //
	ioParams.eccentricity = 0.00403f;
	ioParams.semiMajorLength = 0.4217e6f;
	ioParams.centralBodyMu = jupiter->GetMu();

	jupiter->AddSatellite(std::make_unique<Satellite>(ioParams));
	

	mPlanets.push_back(std::move(jupiter));


	revolutionableBodyParams_t saturnParams;
	memset(&saturnParams, 0, sizeof(revolutionableBodyParams_t));
	saturnParams.base.fileName = "../../../../Blender models/Saturn/Saturn.obj";
	saturnParams.base.name = "Saturn";
	saturnParams.base.initialPosition = glm::vec3(1357.554e6f, 0.f, 0.f);
	saturnParams.base.initialVelocity = glm::vec3(0.f, 0.f, -10.14f);
	saturnParams.base.radius = 58232.f;
	saturnParams.base.mass = 568.32e24f;
	saturnParams.base.scale = 1.3f;
	saturnParams.base.rotationPeriod = 38361.6f;
	saturnParams.base.inclination = glm::radians(26.73f);
	saturnParams.base.simulationInitialDistance = 40.f;
	saturnParams.eccentricity = 0.0520f;
	saturnParams.semiMajorLength = 1357.554e6f;
	saturnParams.centralBodyMu = mSun->GetMu();

	std::unique_ptr<Planet> saturn = std::make_unique<Planet>(saturnParams);


	revolutionableBodyParams_t enceladusParams;
	memset(&enceladusParams, 0, sizeof(revolutionableBodyParams_t));
	enceladusParams.base.fileName = "../../../../Blender models/Enceladus/Enceladus.obj";
	enceladusParams.base.name = "Enceladus";
	enceladusParams.base.initialPosition = glm::vec3(glm::length(saturnParams.base.initialPosition) + 0.237e6f, 0.f, 0.f);
	enceladusParams.base.initialVelocity = glm::vec3(0.f, 0.f, -15.128f);
	enceladusParams.base.radius = 252.1f;
	enceladusParams.base.mass = 0.0001080e24f;
	enceladusParams.base.scale = 0.05f;
	enceladusParams.base.rotationPeriod = 118386.8352f;
	enceladusParams.base.inclination = glm::radians(saturnParams.base.inclination + 0.009f);
	enceladusParams.base.simulationInitialDistance = saturnParams.base.simulationInitialDistance + 1.8f; //
	enceladusParams.eccentricity = 0.0047f;
	enceladusParams.semiMajorLength = 0.237948e6f;
	enceladusParams.centralBodyMu = saturn->GetMu();

	saturn->AddSatellite(std::make_unique<Satellite>(enceladusParams));

	
	revolutionableBodyParams_t mimasParams;
	memset(&mimasParams, 0, sizeof(revolutionableBodyParams_t));
	mimasParams.base.fileName = "../../../../Blender models/Mimas/Mimas.obj";
	mimasParams.base.name = "Mimas";
	mimasParams.base.initialPosition = glm::vec3(glm::length(saturnParams.base.initialPosition) + 0.181902e6f, 0.f, 0.f);
	mimasParams.base.initialVelocity = glm::vec3(0.f, 0.f, -14.28f);
	mimasParams.base.radius = 198.2f;
	mimasParams.base.mass = 0.0000375e24f;
	mimasParams.base.scale = 0.025f;
	mimasParams.base.rotationPeriod = 81425.26f;
	mimasParams.base.inclination = glm::radians(saturnParams.base.inclination + 0.009f);
	mimasParams.base.simulationInitialDistance = saturnParams.base.simulationInitialDistance + 1.574f; //
	mimasParams.eccentricity = 0.0196f;
	mimasParams.semiMajorLength = 0.185539e6f;
	mimasParams.centralBodyMu = saturn->GetMu();

	saturn->AddSatellite(std::make_unique<Satellite>(mimasParams));
	

	
	revolutionableBodyParams_t titanParams;
	memset(&titanParams, 0, sizeof(revolutionableBodyParams_t));
	titanParams.base.fileName = "../../../../Blender models/Titan/Titan.obj";
	titanParams.base.name = "Titan";
	titanParams.base.initialPosition = glm::vec3(glm::length(saturnParams.base.initialPosition) + 1.186680e6f, 0.f, 0.f);
	titanParams.base.initialVelocity = glm::vec3(0.f, 0.f, -5.57f);
	titanParams.base.radius = 2574.73f;
	titanParams.base.mass = 0.13452e24f;
	titanParams.base.scale = 0.17f; //
	titanParams.base.rotationPeriod = 1377648.f;
	titanParams.base.inclination = glm::radians(saturnParams.base.inclination + 0.348f);
	titanParams.base.simulationInitialDistance = saturnParams.base.simulationInitialDistance + 4.5f; //
	titanParams.eccentricity = 0.0288f;
	titanParams.semiMajorLength = 1.22187e6f;
	titanParams.centralBodyMu = saturn->GetMu();

	saturn->AddSatellite(std::make_unique<Satellite>(titanParams));
	
	mPlanets.push_back(std::move(saturn));


	revolutionableBodyParams_t uranosParams;
	memset(&uranosParams, 0, sizeof(revolutionableBodyParams_t));
	uranosParams.base.fileName = "../../../../Blender models/Uranos/Uranos.obj";
	uranosParams.base.name = "Uranos";
	uranosParams.base.initialPosition = glm::vec3(2732.696e6f, 0.f, 0.f);
	uranosParams.base.initialVelocity = glm::vec3(0.f, 0.f, -7.13f);
	uranosParams.base.radius = 25362.f;
	uranosParams.base.mass = 86.811e24f;
	uranosParams.base.scale = 1.35f;
	uranosParams.base.rotationPeriod = 62064.f;
	uranosParams.base.inclination = glm::radians(97.77f);
	uranosParams.base.simulationInitialDistance = 50.f;
	uranosParams.eccentricity = 0.0469f;
	uranosParams.semiMajorLength = 2732.696e6f;
	uranosParams.centralBodyMu = mSun->GetMu();

	mPlanets.push_back(std::make_unique<Planet>(uranosParams));

	revolutionableBodyParams_t neptuneParams;
	memset(&neptuneParams, 0, sizeof(revolutionableBodyParams_t));
	neptuneParams.base.fileName = "../../../../Blender models/Neptune/Neptune.obj";
	neptuneParams.base.name = "Neptune";
	neptuneParams.base.initialPosition = glm::vec3(4471.05e6f, 0.f, 0.f);
	neptuneParams.base.initialVelocity = glm::vec3(0.f, 0.f, -5.47f);
	neptuneParams.base.radius = 24622.f;
	neptuneParams.base.mass = 102.409e24f;
	neptuneParams.base.scale = 1.3f;
	neptuneParams.base.rotationPeriod = 57996.f;
	neptuneParams.base.inclination = glm::radians(23.32f);
	neptuneParams.base.simulationInitialDistance = 60.f;
	neptuneParams.eccentricity = 0.0097f;
	neptuneParams.semiMajorLength = 4471.05e6f;
	neptuneParams.centralBodyMu = mSun->GetMu();

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
		planet->UpdateSatellites(uniformWorldLocation, delta, mPeriodToScale, planet.get());
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
