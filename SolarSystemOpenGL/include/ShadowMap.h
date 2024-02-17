#pragma once

#include <spdlog/spdlog.h>
#include <GL/glew.h>

typedef struct ShadowMapParams{
	GLuint width;
	GLuint height;
} shadowMapParams_t;

class ShadowMap {
public:
	ShadowMap();
	virtual ~ShadowMap();

	virtual bool Init(GLuint width, GLuint height);

	virtual void Write();
	virtual void Read(GLenum textureUnit);

	GLuint GetShadowWidth() const { return mShadowWidth; }
	GLuint GetShadowHeight() const { return mShadowWidth; }

protected:
	GLuint mFBO, mShadowMapID;
	GLuint mShadowWidth, mShadowHeight;
};