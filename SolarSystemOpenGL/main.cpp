#define STB_IMAGE_IMPLEMENTATION

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

using namespace std;

static GLfloat delta = 0.0f;
static GLfloat last = 0.0f;

// vertex shader
static const char* vShader = "../../Shaders/shader.vert";
static const char* vSimpleShader = "../../Shaders/SimpleShader.vert";

// fragment shader
static const char* fShader = "../../Shaders/shader.frag";
static const char* fSimpleShader = "../../Shaders/SimpleShader.frag";


int main(int argc, char** argv)
{

	auto glVersion = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
	SPDLOG_INFO("OpenGL context version: {}", glVersion);

	SPDLOG_INFO("Program start");

	// Window
	constexpr int WIDTH = 1152;
	constexpr int HEIGHT = 864;

	SPDLOG_INFO("Create GLFW window");

	unique_ptr<Window> mainWindow = make_unique<Window>(WIDTH, HEIGHT, 45.f);
	mainWindow->Initialise();

	// Camera
	unique_ptr<Camera> camera = make_unique<Camera>(glm::vec3(10.f, 10.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f), 0.f, 0.0f, 5.0f, 0.5f);

	// Solar system
	unique_ptr<SolarSystem> solarSystem;
	solarSystem = SolarSystem::GetInstance();
	solarSystem->LoadSolarSystem();


	unique_ptr<Shader> simpleShader = make_unique<Shader>();
	simpleShader->CreateFromFiles(vSimpleShader, fSimpleShader);
	
	unique_ptr<Shader> shader = make_unique<Shader>();
	shader->CreateFromFiles(vShader, fShader);
	
	assert(simpleShader->GetBindingPoint() == shader->GetBindingPoint() && "Binding points are not same!");

	GLuint uniformWorld = 0, uniformCameraPosition = 0, UBOMatrices = 0;

	// Generate Uniform Buffer Object
	glGenBuffers(1, &UBOMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, UBOMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, simpleShader->GetBindingPoint(), UBOMatrices, 0, 2 * sizeof(glm::mat4));


	float angle = 0.f;
	// Loop until window closed
	while (!mainWindow->GetShouldClose()) {
		GLfloat current = glfwGetTime(); // SDL_GetPerformanceCounter();
		delta = current - last; // (current - lastTime)*1000/SDL_GetPerformanceFrequency();
		last = current;
		SPDLOG_INFO("delta: {}secs", delta);

		// Get + Handle User Input
		glfwPollEvents();

		camera->KeyControl(mainWindow->GetKeys(), delta);
		camera->MouseControl(mainWindow->GetXChange(), mainWindow->GetYChange());

		// Clear the window
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		simpleShader->UseShader();
		uniformWorld = simpleShader->GetWorldLocation();

		glm::mat4 projection = glm::perspective(glm::radians(mainWindow->GetFOV()), mainWindow->GetBufferWidth() / static_cast<GLfloat>(mainWindow->GetBufferHeight()), 0.1f, 500.f);
		glBindBuffer(GL_UNIFORM_BUFFER, UBOMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBuffer(GL_UNIFORM_BUFFER, UBOMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera->CalcViewMatrix()));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		solarSystem->UpdateSun(uniformWorld, delta);


		shader->UseShader();
		uniformWorld = shader->GetWorldLocation();
		uniformCameraPosition = shader->GetCameraPositionLocation();
		glUniform3f(uniformCameraPosition, camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);

		
		// Draw object
		solarSystem->UpdatePlanets(shader.get(), uniformWorld, delta);

		glUseProgram(0);
		mainWindow->SwapBuffers();
	}

	// Delete Uniform Buffer Object
	glDeleteBuffers(1, &UBOMatrices);

	return 0;
}