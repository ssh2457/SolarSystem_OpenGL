#include "include/Star.h"

Star::Star(starParams_t& starParams)
	: SpaceObject(starParams.base.fileName, starParams.base.name,
		starParams.base.initialPosition, starParams.base.initialVelocity,
		starParams.base.radius, starParams.base.mass,
		starParams.base.scale, starParams.base.rotationPeriod, starParams.base.inclination)
	, mPointLight(nullptr) {

	pointLightParams_t pointLightParams;
	memset(&pointLightParams, 0, sizeof(pointLightParams_t));
	pointLightParams.base.red = 1.f;
	pointLightParams.base.green = 1.f;
	pointLightParams.base.blue = 1.f;

	pointLightParams.base.ambientIntensity = 0.025f;
	pointLightParams.base.diffuseIntensity = 1.0f;

	pointLightParams.posX = mInitialPosition.x;
	pointLightParams.posY = mInitialPosition.y;
	pointLightParams.posZ = mInitialPosition.z;

	pointLightParams.con = 1.f;
	pointLightParams.lin = 0.0001f;
	pointLightParams.exp = 0.00001f;

	mPointLight = std::make_unique<PointLight>(pointLightParams.base.red, pointLightParams.base.green, pointLightParams.base.blue,
												pointLightParams.base.ambientIntensity, pointLightParams.base.diffuseIntensity,
												pointLightParams.posX, pointLightParams.posY, pointLightParams.posZ,
												pointLightParams.con, pointLightParams.lin, pointLightParams.exp);
}

PointLight* Star::GetPointLight() const {
	return mPointLight.get();
}
