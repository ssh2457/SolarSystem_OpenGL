#include "include/Graphic.h"

std::unique_ptr<Graphic> Graphic::instance = nullptr;

Graphic::Graphic()
	: mSimpleShader(nullptr)
	, mShader(nullptr)
	, mOmniShadowShader(nullptr)
	, mPointLight(nullptr)
	, mUniformWorld(0)
	, mUniformCameraPosition(0)
	, mUBOMatrices(0)
	, mUniformOmniLightPos(0)
	, mUniformFarPlane(0)
	, mProjection(glm::mat4(1.f))
{
	mSimpleShader = std::make_unique<SimpleShader>();
	mSimpleShader->CreateFromFiles(vSimpleShader, fSimpleShader);

	mShader = std::make_unique<Shader>();
	mShader->CreateFromFiles(vShader, fShader);

	mOmniShadowShader = std::make_unique<Shader>();
	mOmniShadowShader->CreateFromFiles(vOmniShadowShader, gOmniShadowShader, fOmniShadowShader);

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("../../Textures/Skybox/space_rt.png");
	skyboxFaces.push_back("../../Textures/Skybox/space_lf.png");
	skyboxFaces.push_back("../../Textures/Skybox/space_up.png");
	skyboxFaces.push_back("../../Textures/Skybox/space_dn.png");
	skyboxFaces.push_back("../../Textures/Skybox/space_bk.png");
	skyboxFaces.push_back("../../Textures/Skybox/space_ft.png");

	mSkybox = std::make_unique<SkyBox>(skyboxFaces);

	pointLightParams_t pointLightParams;
	memset(&pointLightParams, 0, sizeof(pointLightParams_t));
	pointLightParams.base.red = 1.f;
	pointLightParams.base.green = 1.f;
	pointLightParams.base.blue = 1.f;

	pointLightParams.base.ambientIntensity = 0.025f;
	pointLightParams.base.diffuseIntensity = 1.0f;

	pointLightParams.base.shadowMapParams.width = 1920;
	pointLightParams.base.shadowMapParams.height = 1920;

	pointLightParams.posX = 0;
	pointLightParams.posY = 0;
	pointLightParams.posZ = 0;

	pointLightParams.con = 1.f;
	pointLightParams.lin = 0.0001f;
	pointLightParams.exp = 0.00001f;

	mPointLight = std::make_unique<PointLight>(pointLightParams, 0.1f, 500.f);

	// Generate Uniform Buffer Object
	glGenBuffers(1, &mUBOMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, mUBOMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, mSimpleShader->GetBindingPoint(), mUBOMatrices, 0, 2 * sizeof(glm::mat4));
}

void Graphic::UpdateProjection(Window* window)
{
	mProjection = glm::perspective(glm::radians(window->GetFOV()), window->GetBufferWidth() / static_cast<GLfloat>(window->GetBufferHeight()), 0.1f, 500.f);
}

Graphic::~Graphic()
{
	glDeleteBuffers(1, &mUBOMatrices);
}

std::unique_ptr<Graphic> Graphic::GetInstance()
{
	if (instance == nullptr) {
		instance = std::make_unique<Graphic>();
		SPDLOG_INFO("A Graphic instance is created");
		return std::move(instance);
	}
	return std::move(instance);
}

void Graphic::OmniShadowMapPass(SolarSystem* solarSystem, float delta)
{
	// Render shadow
	mOmniShadowShader->UseShader();

	glViewport(0, 0, mPointLight->GetShadowMap()->GetShadowWidth(), mPointLight->GetShadowMap()->GetShadowHeight());

	mUniformWorld = mOmniShadowShader->GetWorldLocation();
	mUniformOmniLightPos = mOmniShadowShader->GetOmniLightPosLocation();
	mUniformFarPlane = mOmniShadowShader->GetFarPlaneLocation();

	mPointLight->GetShadowMap()->Write();

	glClear(GL_DEPTH_BUFFER_BIT);

	glm::vec3 lightPos = mPointLight->GetPosition();

	glUniform3f(mUniformOmniLightPos, lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(mUniformFarPlane, mPointLight->GetFarPlane());
	mOmniShadowShader->SetLightMatrices(mPointLight->CalcLightTransform());
	mOmniShadowShader->Validate();

	solarSystem->UpdatePlanets(mUniformWorld, delta / 2.f);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Graphic::RenderPass(SolarSystem* solarSystem, float delta, Window* window, Camera* camera)
{
	UpdateProjection(window);

	// Render planets
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mSkybox->DrawSkyBox(mUBOMatrices, camera->CalcViewMatrix(), mProjection);

	mShader->UseShader();

	// Clear the window
	glViewport(0, 0, window->GetBufferWidth(), window->GetBufferHeight());


	mUniformWorld = mShader->GetWorldLocation();
	mUniformCameraPosition = mShader->GetCameraPositionLocation();

	glUniform3f(mUniformCameraPosition, camera->GetCameraPosition().x, camera->GetCameraPosition().y, camera->GetCameraPosition().z);

	glBindBuffer(GL_UNIFORM_BUFFER, mUBOMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(mProjection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, mUBOMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera->CalcViewMatrix()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	mPointLight->SetPosition(solarSystem->GetSun()->GetCurrentPosition());
	mShader->SetPointLight(mPointLight.get(), 1);


	mPointLight->GetShadowMap()->Read(GL_TEXTURE1);
	mShader->SetTexture(0);
	mShader->Validate();

	solarSystem->UpdatePlanets(mUniformWorld, delta / 2.f);


	// Render the Sun
	mSimpleShader->UseShader();
	mUniformWorld = mSimpleShader->GetWorldLocation();
	mSimpleShader->Validate();
	solarSystem->UpdateSun(mUniformWorld, delta);
}
