#include <assimp/Importer.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <spdlog/spdlog.h>

#include <iostream>

#include <cassert>
#include <memory>
#include <utility>
#include <fstream>

#include "include/Common.h"
#include "include/Camera.h"
#include "include/SimpleShader.h"
#include "include/Shader.h"
#include "include/Window.h"
#include "include/SolarSystem.h"
#include "include/Model.h"
#include "include/Graphic.h"
#include "include/SkyBox.h"

using namespace std;

static GLfloat delta = 0.0f;
static GLfloat last = 0.0f;

int main(int argc, char** argv)
{
	auto glVersion = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
	SPDLOG_INFO("OpenGL context version: {}", glVersion);

	SPDLOG_INFO("Program start");

	// Window
	constexpr int WIDTH = 1366;
	constexpr int HEIGHT = 768;

	SPDLOG_INFO("Create GLFW window");

	unique_ptr<Window> mainWindow = make_unique<Window>(WIDTH, HEIGHT, 60.f);
	mainWindow->Initialise();

	// Camera
	unique_ptr<Camera> camera = make_unique<Camera>(glm::vec3(10.f, 10.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f), 0.f, 0.0f, 5.0f, 0.5f);

	// Solar system
	unique_ptr<SolarSystem> solarSystem;
	solarSystem = SolarSystem::GetInstance();
	solarSystem->LoadSolarSystem();

	// Graphic controller
	unique_ptr<Graphic> graphic_controller;
	graphic_controller = Graphic::GetInstance();

	float angle = 0.f;
	last = glfwGetTime();

	// Loop until window closed
	while (!mainWindow->GetShouldClose()) {
		GLfloat current = glfwGetTime(); // SDL_GetPerformanceCounter();
		delta = current - last;
		last = current;


		// Get + Handle User Input
		glfwPollEvents();

		camera->KeyControl(mainWindow->GetKeys(), delta);
		camera->MouseControl(mainWindow->GetXChange(), mainWindow->GetYChange());

		graphic_controller->OmniShadowMapPass(solarSystem.get(), delta);
		graphic_controller->RenderPass(solarSystem.get(), delta, mainWindow.get(), camera.get());

		glUseProgram(0);
		mainWindow->SwapBuffers();
	}
	return 0;
}