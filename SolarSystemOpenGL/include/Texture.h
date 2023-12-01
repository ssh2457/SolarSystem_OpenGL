#pragma once

#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include "stb_image.h"

class Texture {
public:
	Texture() = delete;
	Texture(const char* filePath);
	virtual ~Texture();

	bool LoadTexture();
	bool LoadTextureA();

	void UseTexture();
	void ClearTexture();
private:
	GLuint mTextureID;
	int mWidth, mHeight, mBitDepth;
	const char* mFilePath;

};