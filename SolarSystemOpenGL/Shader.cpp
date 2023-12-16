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
	, mUniformExponent(0) {

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

void Shader::SetPointLight(PointLight* light) {
	light->UseLight(mUniformLightColour,
					mUniformAmbientIntensity, mUniformDiffuseIntensity,
					mUniformLightPosition,
					mUniformConstant, mUniformLinear, mUniformExponent);
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

	glValidateProgram(mShaderID);
	glGetProgramiv(mShaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(mShaderID, sizeof(eLog), NULL, eLog);
		SPDLOG_ERROR("Error validating program: {}", eLog);
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
}
