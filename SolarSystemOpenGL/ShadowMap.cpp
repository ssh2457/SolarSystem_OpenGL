#include "include/ShadowMap.h"

ShadowMap::ShadowMap()
	: mFBO(0)
	, mShadowMapID(0)
	, mShadowWidth(0)
	, mShadowHeight(0)
{

}

ShadowMap::~ShadowMap()
{
	if (mFBO) {
		glDeleteFramebuffers(1, &mFBO);
	}

	if (mShadowMapID) {
		glDeleteTextures(1, &mShadowMapID);
	}
}

bool ShadowMap::Init(GLuint width, GLuint height)
{
	mShadowWidth = width;
	mShadowHeight = height;


	// Generate a framebuffer for shadow
	glGenFramebuffers(1, &mFBO);

	// Generate a shadow texture
	glGenTextures(1, &mShadowMapID);
	glBindTexture(GL_TEXTURE_2D, mShadowMapID);

	/*
	* GL_TEXTURE_2D: the texture is 2D
	* GL_DEPTH_COMPONENT: has 1 channel which has a value between 0 and 1.
	* Hence, FBO contains the depth.
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mShadowWidth, mShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Bind the FBO as GL_FRAMEBUFFER
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	// Connect the framebuffer to the texture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mShadowMapID, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE)
	{
		SPDLOG_INFO("Framebuffer for shadowMap error!: {}", Status);
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void ShadowMap::Write()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
}

void ShadowMap::Read(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, mShadowMapID);
}
