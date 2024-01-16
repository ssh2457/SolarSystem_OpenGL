#include "include/Planet.h"

Planet::Planet(planetParams_t& planetParams)
	: Satellite(planetParams.base)
{

}

void Planet::AddSatellite(satelliteParams_t& satellite)
{
	satellites.push_back(std::make_unique<Satellite>(satellite));
}

void Planet::LoadSatelliteModels()
{
	for (auto& satellite : satellites) {
		satellite->LoadModel(satellite->GetFilePath());
	}
}

void Planet::UpdateSatellites(GLuint uniformWorldLocation, GLfloat delta, GLfloat periodToScale)
{
	for (auto& satellite : satellites) {
		satellite->Revolve(delta, periodToScale, GetCurrentPosition());
		satellite->Update(uniformWorldLocation, delta, periodToScale);
		satellite->RenderModel();
	}
}
