#pragma once

#include <spdlog/spdlog.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "SimpleShader.h"
#include "Shader.h"
#include "SkyBox.h"
#include "SolarSystem.h"
#include "Window.h"

#include <iostream>
#include<memory>

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


class Graphic {
	friend std::unique_ptr<Graphic> std::make_unique<Graphic>();
	friend std::unique_ptr<Graphic>::deleter_type;
public:
	Graphic(const Graphic& other) = delete;
	Graphic& operator=(const Graphic& other) = delete;

	static std::unique_ptr<Graphic> GetInstance();

	void OmniShadowMapPass(SolarSystem* solarSystem, float delta);
	void RenderPass(SolarSystem* solarSystem, float delta, Window* window, Camera* camera);
private:

	Graphic();
	virtual ~Graphic();

	static std::unique_ptr<Graphic> instance;

	std::unique_ptr<SimpleShader> mSimpleShader;
	std::unique_ptr<Shader> mShader;
	std::unique_ptr<Shader> mOmniShadowShader;

	std::unique_ptr<SkyBox> mSkybox;

	std::unique_ptr<PointLight> mPointLight;

	GLuint mUniformWorld, mUniformCameraPosition, mUBOMatrices, mUniformOmniLightPos, mUniformFarPlane;

	glm::mat4 mProjection;

	void UpdateProjection(Window* window);
};