#define STB_IMAGE_IMPLEMENTATION

#include <assimp/Importer.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <spdlog/spdlog.h>


#include <memory>
#include <utility>
#include <fstream>

#include "include/Common.h"
#include "include/Camera.h"
#include "include/Shader.h"
#include "include/Window.h"
#include "include/SolarSystem.h"
#include "include/Model.h"

using namespace std;

static GLfloat delta = 0.0f;
static GLfloat last = 0.0f;

// vertex shader
static const char* vShader = "../../Shaders/shader.vert";

// fragment shader
static const char* fShader = "../../Shaders/shader.frag";

int main(int argc, char** argv)
{
	// Window
	constexpr int WIDTH = 1152;
	constexpr int HEIGHT = 864;

	SPDLOG_INFO("Create GLFW window");

	unique_ptr<Window> mainWindow = make_unique<Window>(WIDTH, HEIGHT, 45.f);
	mainWindow->Initialise();

	// Camera
	unique_ptr<Camera> camera = make_unique<Camera>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f), 0.f, 0.0f, 5.0f, 0.5f);

	// Solar system
	unique_ptr<SolarSystem> solarSystem;
	solarSystem = SolarSystem::GetInstance();
	solarSystem->LoadSolarSystem();


	unique_ptr<Shader> shader = make_unique<Shader>();
	shader->CreateFromFiles(vShader, fShader);
	
	unique_ptr<Model> xWing = make_unique<Model>();
	xWing->LoadModel("../../Models/Xwing/x-wing.obj");


	GLuint uniformProjection = 0, uniformView = 0, uniformWorld = 0, uniformCameraPosition = 0;


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

		shader->UseShader();
		uniformWorld = shader->GetWorldLocation();
		uniformView = shader->GetViewLocation();
		uniformProjection = shader->GetProjectionLocation();
		uniformCameraPosition = shader->GetCameraPositionLocation();

		glm::mat4 projection = glm::perspective(glm::radians(mainWindow->GetFOV()), mainWindow->GetBufferWidth() / static_cast<GLfloat>(mainWindow->GetBufferHeight()), 0.1f, 100.f);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->CalcViewMatrix()));
		glUniform3f(uniformCameraPosition, camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);

		
		// Draw object
		glm::mat4 model(1.f);
		model = glm::translate(model, glm::vec3(5.f, 0.f, 0.f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		glUniformMatrix4fv(uniformWorld, 1, GL_FALSE, glm::value_ptr(model));
		xWing->RenderModel();

		solarSystem->Tick(uniformWorld, delta);

		glUseProgram(0);
		mainWindow->SwapBuffers();
	}

	xWing->ClearModel();

	return 0;
}