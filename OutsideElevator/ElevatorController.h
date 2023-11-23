#pragma once
#include "Simulatable.h"
#include <queue>

class SensorProvider;
class ControlProvider;
class ElevatorController : public Simulatable
{
private:

	SensorProvider* _sensors = nullptr;
	ControlProvider* _controls = nullptr;
	std::queue<int> _stops;

public:

	void Init(SensorProvider* sensors, ControlProvider* controls);
	void Step(float deltaTime) override;
	void addStops(std::queue<int> floors);
};

