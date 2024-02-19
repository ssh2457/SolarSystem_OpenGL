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
#include "include/Graphic.h"
//#include "include/SkyBox.h"

using namespace std;

static GLfloat delta = 0.0f;
static GLfloat last = 0.0f;

// vertex shader
static const char* vShader = "../../Shaders/shader.vert";
static const char* vSimpleShader = "../../Shaders/SimpleShader.vert";
static const char* vOmniShadowShader = "../../Shaders/omni_directional_shadow_map.vert";

// fragment shader
static const char* fShader = "../../Shaders/shader.frag";
static const char* fSimpleShader = "../../Shaders/SimpleShader.frag";
static const char* fOmniShadowShader = "../../Shaders/omni_directional_shadow_map.frag";

// geometry shader
static const char* gOmniShadowShader = "../../Shaders/omni_directional_shadow_map.geom";


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


	unique_ptr<SimpleShader> simpleShader = make_unique<SimpleShader>();
	simpleShader->CreateFromFiles(vSimpleShader, fSimpleShader);

	unique_ptr<Shader> shader = make_unique<Shader>();
	shader->CreateFromFiles(vShader, fShader);

	unique_ptr<Shader> omniShadowShader = make_unique<Shader>();
	omniShadowShader->CreateFromFiles(vOmniShadowShader, gOmniShadowShader, fOmniShadowShader);


	vector<string> skyboxFaces;
	skyboxFaces.push_back("../../Textures/Skybox/space_rt.jpg");
	skyboxFaces.push_back("../../Textures/Skybox/space_lf.jpg");
	skyboxFaces.push_back("../../Textures/Skybox/space_up.jpg");
	skyboxFaces.push_back("../../Textures/Skybox/space_dn.jpg");
	skyboxFaces.push_back("../../Textures/Skybox/space_bk.jpg");
	skyboxFaces.push_back("../../Textures/Skybox/space_ft.jpg");

	//unique_ptr<SkyBox> skybox = make_unique<SkyBox>(skyboxFaces);



	assert(simpleShader->GetBindingPoint() == shader->GetBindingPoint() && "Binding points are not same!");

	pointLightParams_t pointLightParams;
	memset(&pointLightParams, 0, sizeof(pointLightParams_t));
	pointLightParams.base.red = 1.f;
	pointLightParams.base.green = 1.f;
	pointLightParams.base.blue = 1.f;

	pointLightParams.base.ambientIntensity = 0.025f;
	pointLightParams.base.diffuseIntensity = 1.0f;

	pointLightParams.base.shadowMapParams.width = 1024;
	pointLightParams.base.shadowMapParams.height = 1024;

	pointLightParams.posX = 0;
	pointLightParams.posY = 0;
	pointLightParams.posZ = 0;

	pointLightParams.con = 1.f;
	pointLightParams.lin = 0.0001f;
	pointLightParams.exp = 0.00001f;

	unique_ptr<PointLight> pointLight = std::make_unique<PointLight>(pointLightParams, 0.1f, 500.f);

	GLuint uniformWorld = 0, uniformCameraPosition = 0, UBOMatrices = 0, uniformOmniLightPos = 0, uniformFarPlane = 0;

	// Generate Uniform Buffer Object
	glGenBuffers(1, &UBOMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, UBOMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, simpleShader->GetBindingPoint(), UBOMatrices, 0, 2 * sizeof(glm::mat4));


	glm::mat4 projection = glm::perspective(glm::radians(mainWindow->GetFOV()), mainWindow->GetBufferWidth() / static_cast<GLfloat>(mainWindow->GetBufferHeight()), 0.1f, 500.f);

	float angle = 0.f;
	last = glfwGetTime();
	// Loop until window closed
	while (!mainWindow->GetShouldClose()) {
		GLfloat current = glfwGetTime(); // SDL_GetPerformanceCounter();
		delta = current - last; // (current - lastTime)*1000/SDL_GetPerformanceFrequency();
		last = current;
		// SPDLOG_INFO("delta: {}secs", delta);

		// Get + Handle User Input
		glfwPollEvents();

		camera->KeyControl(mainWindow->GetKeys(), delta);
		camera->MouseControl(mainWindow->GetXChange(), mainWindow->GetYChange());

	
		// Render shadow
		omniShadowShader->UseShader();

		glViewport(0, 0, pointLight->GetShadowMap()->GetShadowWidth(), pointLight->GetShadowMap()->GetShadowHeight());

		uniformWorld = omniShadowShader->GetWorldLocation();
		uniformOmniLightPos = omniShadowShader->GetOmniLightPosLocation();
		uniformFarPlane = omniShadowShader->GetFarPlaneLocation();

		pointLight->GetShadowMap()->Write();

		glClear(GL_DEPTH_BUFFER_BIT);

		glUniform3f(uniformOmniLightPos, pointLight->GetPosition().x, pointLight->GetPosition().y, pointLight->GetPosition().z);
		glUniform1f(uniformFarPlane, pointLight->GetFarPlane());
		omniShadowShader->SetLightMatrices(pointLight->CalcLightTransform());
		omniShadowShader->Validate();

		solarSystem->UpdatePlanets(uniformWorld, delta / 2.f);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		
		// Render planets
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//skybox->DrawSkyBox(UBOMatrices, camera->CalcViewMatrix(), projection);

		shader->UseShader();

			// Clear the window
		glViewport(0, 0, mainWindow->GetBufferWidth(), mainWindow->GetBufferHeight());


		uniformWorld = shader->GetWorldLocation();
		uniformCameraPosition = shader->GetCameraPositionLocation();

		glUniform3f(uniformCameraPosition, camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);

		glBindBuffer(GL_UNIFORM_BUFFER, UBOMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBuffer(GL_UNIFORM_BUFFER, UBOMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera->CalcViewMatrix()));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		pointLight->SetPosition(solarSystem->GetSun()->GetCurrentPosition());
		shader->SetPointLight(pointLight.get(), 1);


		pointLight->GetShadowMap()->Read(GL_TEXTURE1);
		shader->SetTexture(0);
		shader->Validate();

		solarSystem->UpdatePlanets(uniformWorld, delta / 2.f);


		// Render the Sun
		simpleShader->UseShader();
		uniformWorld = simpleShader->GetWorldLocation();
		simpleShader->Validate();
		solarSystem->UpdateSun(uniformWorld, delta);

		glUseProgram(0);
		mainWindow->SwapBuffers();
	}

	// Delete Uniform Buffer Object
	glDeleteBuffers(1, &UBOMatrices);

	return 0;
}