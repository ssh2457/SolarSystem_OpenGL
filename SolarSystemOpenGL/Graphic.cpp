#include "include/Graphic.h"

std::unique_ptr<Graphic> Graphic::instance = nullptr;

std::unique_ptr<Graphic> Graphic::GetInstance()
{
	if (instance == nullptr) {
		instance = std::make_unique<Graphic>();
		return std::move(instance);
	}
	return std::move(instance);
}

Graphic::~Graphic()
{
	instance = nullptr;
}

