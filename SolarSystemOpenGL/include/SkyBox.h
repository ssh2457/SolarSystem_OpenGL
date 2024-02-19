#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <spdlog/spdlog.h>

#include "stb_image.h"
#include "Mesh.h"
#include "Shader.h"

#include <vector>
#include <string>

class SkyBox {
public:
	SkyBox() = delete;
	SkyBox(std::vector<std::string> faceLocations);
	virtual ~SkyBox() = default;

	void DrawSkyBox(const GLuint UBOMatrices, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	std::unique_ptr<Mesh> mSkyMesh;
	std::unique_ptr<Shader> mSkyShader;

	GLuint mTextureID;
};
