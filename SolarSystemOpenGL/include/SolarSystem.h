#pragma once

#include <spdlog/spdlog.h>

#include<memory>

class SolarSystem {
	friend std::unique_ptr<SolarSystem> std::make_unique<SolarSystem>();
	friend std::unique_ptr<SolarSystem>::deleter_type;
public:
	SolarSystem(const SolarSystem& ) = delete;
	SolarSystem& operator=(const SolarSystem&) = delete;
	
	static std::unique_ptr<SolarSystem> GetInstance();
private:
	SolarSystem() = default;
	virtual ~SolarSystem() = default;

	static std::unique_ptr<SolarSystem> instance;
};