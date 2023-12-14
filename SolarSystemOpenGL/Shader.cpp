#include "include/Shader.h"

Shader::Shader()
	: mShaderID(0)
	, mUniformProjection(0)
	, mUniformWorld(0)
	, mUniformView(0)
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

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode = ReadFile(vertexPath);
	std::string fragmentCode = ReadFile(fragmentPath);

	CreateFromString(vertexCode.c_str(), fragmentCode.c_str());
}

std::string Shader::ReadFile(const char* filePath) {
	std::string content = "";
	std::ifstream fileStream(filePath, std::ios::in);
	if (!fileStream.is_open()) {
		SPDLOG_ERROR("Failed to read {}! File doesn't exist", filePath);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + '\n');
	}
	fileStream.close();

	return content;
}

void Shader::UseShader() {
	glUseProgram(mShaderID);
}

void Shader::ClearShader() {
	if (mShaderID != 0) {
		glDeleteProgram(mShaderID);
		mShaderID = 0;
	}

	mUniformWorld = 0;
	mUniformView = 0;
	mUniformProjection = 0;
}

GLuint Shader::GetWorldLocation() const {
	return mUniformWorld;
}

GLuint Shader::GetViewLocation() const {
	return mUniformView;
}

GLuint Shader::GetProjectionLocation() const {
	return mUniformProjection;
}

GLuint Shader::GetCameraPositionLocation() const {
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


	mUniformWorld = glGetUniformLocation(mShaderID, "world");
	mUniformView = glGetUniformLocation(mShaderID, "view");
	mUniformProjection = glGetUniformLocation(mShaderID, "projection");
	mUniformCameraPosition = glGetUniformLocation(mShaderID, "cameraPosition");

	mUniformLightColour = glGetUniformLocation(mShaderID, "lightColour");

	mUniformAmbientIntensity = glGetUniformLocation(mShaderID, "ambientIntensity");
	mUniformDiffuseIntensity = glGetUniformLocation(mShaderID, "diffuseIntensity");

	mUniformLightPosition = glGetUniformLocation(mShaderID, "lightPosition");

	mUniformConstant = glGetUniformLocation(mShaderID, "constant");
	mUniformLinear = glGetUniformLocation(mShaderID, "linear");
	mUniformExponent = glGetUniformLocation(mShaderID, "exponent");
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* const* theCode = &shaderCode;
	GLint codeLength = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, &codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[512] = { 0, };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		SPDLOG_ERROR("Error compiling the {} shader: {}", shaderType, eLog);
		//printf("Error compiling the %d shader: %s\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

