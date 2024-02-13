#include "include/Planet.h"

Planet::Planet(revolutionableBodyParams_t& planetParams)
	: RevolutionableBody(planetParams)
{

}

void Planet::AddSatellite(std::unique_ptr<Satellite> satellite)
{
	satellites.push_back(std::move(satellite));
}

void Planet::LoadSatelliteModels()
{
	for (auto& satellite : satellites) {
		satellite->LoadModel(satellite->GetFilePath());
	}
}

void Planet::UpdateSatellites(GLuint uniformWorldLocation, GLfloat delta, GLfloat periodToScale, Planet* governingPlanet)
{
	for (auto& satellite : satellites) {
		satellite->Revolve(delta, periodToScale, GetCurrentPosition());
		satellite->Update(uniformWorldLocation, delta, periodToScale, governingPlanet);
		satellite->RenderModel();
	}
}
