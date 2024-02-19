#include "include/Shader.h"

Shader::Shader()
	: SimpleShader()
	, mUniformCameraPosition(0)
	, mUniformLightColour(0)
	, mUniformAmbientIntensity(0)
	, mUniformDiffuseIntensity(0)
	, mUniformLightPosition(0)
	, mUniformConstant(0)
	, mUniformLinear(0)
	, mUniformExponent(0)
	, mUniformTexture(0)
{

}

Shader::~Shader() {
	ClearShader();
}

void Shader::ClearShader() {
	if (mShaderID != 0) {
		glDeleteProgram(mShaderID);
		mShaderID = 0;
	}

	mUniformCameraPosition = 0;

	mUniformLightColour = 0;

	mUniformAmbientIntensity = 0;
	mUniformDiffuseIntensity = 0;

	mUniformLightPosition = 0;

	mUniformConstant = 0;
	mUniformLinear = 0;
	mUniformExponent = 0;

	mUniformTexture = 0;
}


void Shader::CreateFromFiles(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode = ReadFile(vertexPath);
	std::string fragmentCode = ReadFile(fragmentPath);

	CompileShader(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::CreateFromFiles(const char* vertexPath, const char* geometryPath, const char* fragmentPath)
{
	std::string vertexCode = ReadFile(vertexPath);
	std::string geometryCode = ReadFile(geometryPath);
	std::string fragmentCode = ReadFile(fragmentPath);

	CompileShader(vertexCode.c_str(), geometryCode.c_str(), fragmentCode.c_str());
}


GLuint Shader::GetCameraPositionLocation() const
{
	return mUniformCameraPosition;
}

GLuint Shader::GetLightCoulourLocation() const {
	return mUniformLightColour;
}

GLuint Shader::GetAmbientIntensityLocation() const {
	return mUniformAmbientIntensity;
}

GLuint Shader::GetDiffuseIntensityLocation() const {
	return mUniformDiffuseIntensity;
}

GLuint Shader::GetLightPositionLocation() const {
	return mUniformLightPosition;
}

GLuint Shader::GetConstantLocation() const {
	return mUniformConstant;
}

GLuint Shader::GetLinearLocation() const {
	return mUniformLinear;
}

GLuint Shader::GetExponentLocation() const {
	return mUniformExponent;
}

void Shader::SetPointLight(PointLight* light, GLuint textureUnit) {
	light->UseLight(mUniformLightColour,
		mUniformAmbientIntensity, mUniformDiffuseIntensity,
		mUniformLightPosition,
		mUniformConstant, mUniformLinear, mUniformExponent);

	light->GetShadowMap()->Read(GL_TEXTURE0 + textureUnit);
	glUniform1i(mUniformOmniShadowMap.shadowMap, textureUnit);
	glUniform1f(mUniformOmniShadowMap.farPlane, light->GetFarPlane());
}

void Shader::SetTexture(const GLuint textureUnit)
{
	glUniform1i(mUniformTexture, textureUnit);
}

void Shader::SetLightMatrices(std::vector<glm::mat4> lightMatrices)
{
	for (size_t i = 0; i < 6; ++i) {
		glUniformMatrix4fv(mUniformLightMatrices[i], 1, GL_FALSE, glm::value_ptr(lightMatrices[i]));
	}
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
	mShaderID = glCreateProgram();
	if (!mShaderID) {
		SPDLOG_ERROR("Error creating shader program!");
		return;
	}

	AddShader(mShaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(mShaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[512] = { 0, };

	glLinkProgram(mShaderID);
	glGetProgramiv(mShaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(mShaderID, sizeof(eLog), NULL, eLog);
		SPDLOG_ERROR("Error linking program: {}", eLog);
		return;
	}

	mUniformBlock = glGetUniformBlockIndex(mShaderID, "Matrices");
	glUniformBlockBinding(mShaderID, mUniformBlock, mBindingPoint);

	mUniformWorld = glGetUniformLocation(mShaderID, "world");

	mUniformCameraPosition = glGetUniformLocation(mShaderID, "cameraPosition");

	mUniformLightColour = glGetUniformLocation(mShaderID, "lightColour");

	mUniformAmbientIntensity = glGetUniformLocation(mShaderID, "ambientIntensity");
	mUniformDiffuseIntensity = glGetUniformLocation(mShaderID, "diffuseIntensity");

	mUniformLightPosition = glGetUniformLocation(mShaderID, "lightPosition");

	mUniformConstant = glGetUniformLocation(mShaderID, "constant");
	mUniformLinear = glGetUniformLocation(mShaderID, "linear");
	mUniformExponent = glGetUniformLocation(mShaderID, "exponent");

	// for shadowMap
	mUniformTexture = glGetUniformLocation(mShaderID, "theTexture");


	mUniformOmniLightPos = glGetUniformLocation(mShaderID, "lightPos");
	mUniformFarPlane = glGetUniformLocation(mShaderID, "farPlane");

	for (size_t i = 0; i < 6; ++i) {
		char locBuff[128] = { '\0', };

		snprintf(locBuff, sizeof(locBuff), "lightMatrices[%d]", i);
		mUniformLightMatrices[i] = glGetUniformLocation(mShaderID, locBuff);
	}

	mUniformOmniShadowMap.shadowMap = glGetUniformLocation(mShaderID, "omnishadowMap.shadowMap");
	mUniformOmniShadowMap.farPlane = glGetUniformLocation(mShaderID, "omnishadowMap.farPlane");
}

void Shader::CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode)
{
	mShaderID = glCreateProgram();
	if (!mShaderID) {
		SPDLOG_ERROR("Error creating shader program!");
		return;
	}

	AddShader(mShaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(mShaderID, geometryCode, GL_GEOMETRY_SHADER);
	AddShader(mShaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[512] = { 0, };

	glLinkProgram(mShaderID);
	glGetProgramiv(mShaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(mShaderID, sizeof(eLog), NULL, eLog);
		SPDLOG_ERROR("Error linking program: {}", eLog);
		return;
	}

	mUniformBlock = glGetUniformBlockIndex(mShaderID, "Matrices");
	glUniformBlockBinding(mShaderID, mUniformBlock, mBindingPoint);

	mUniformWorld = glGetUniformLocation(mShaderID, "world");

	mUniformCameraPosition = glGetUniformLocation(mShaderID, "cameraPosition");

	mUniformLightColour = glGetUniformLocation(mShaderID, "lightColour");

	mUniformAmbientIntensity = glGetUniformLocation(mShaderID, "ambientIntensity");
	mUniformDiffuseIntensity = glGetUniformLocation(mShaderID, "diffuseIntensity");

	mUniformLightPosition = glGetUniformLocation(mShaderID, "lightPosition");

	mUniformConstant = glGetUniformLocation(mShaderID, "constant");
	mUniformLinear = glGetUniformLocation(mShaderID, "linear");
	mUniformExponent = glGetUniformLocation(mShaderID, "exponent");

	// for shadowMap
	mUniformTexture = glGetUniformLocation(mShaderID, "theTexture");


	mUniformOmniLightPos = glGetUniformLocation(mShaderID, "lightPos");
	mUniformFarPlane = glGetUniformLocation(mShaderID, "farPlane");

	for (size_t i = 0; i < 6; ++i) {
		char locBuff[128] = { '\0', };

		snprintf(locBuff, sizeof(locBuff), "lightMatrices[%d]", i);
		mUniformLightMatrices[i] = glGetUniformLocation(mShaderID, locBuff);
	}

	mUniformOmniShadowMap.shadowMap = glGetUniformLocation(mShaderID, "omnishadowMap.shadowMap");
	mUniformOmniShadowMap.farPlane = glGetUniformLocation(mShaderID, "omnishadowMap.farPlane");
}
