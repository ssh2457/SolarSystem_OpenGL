#pragma once

#include <spdlog/spdlog.h>
#include <GL/glew.h>

class ShadowMap {
public:
	ShadowMap();
	virtual ~ShadowMap();

	virtual bool Init(GLuint width, GLuint height);

	virtual void Write();
	virtual void Read(GLenum textureUnit);

	GLuint GetShadowWidth() { return mShadowWidth; }
	GLuint GetShadowHeight() { return mShadowWidth; }

protected:
	GLuint mFBO, mShadowMapID;
	GLuint mShadowWidth, mShadowHeight;
};