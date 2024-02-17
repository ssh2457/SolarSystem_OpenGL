#pragma once

#include "ShadowMap.h"

class OmniShadowMap : public ShadowMap {
public:
	OmniShadowMap();

	virtual bool Init(unsigned int width, unsigned int height) override;

	virtual void Write() override;

	virtual void Read(GLenum TextureUnit) override;

	~OmniShadowMap();
};

