#pragma once
#include "Simulatable.h"
#include <queue>
#include <chrono>
#include <list>

class SensorProvider;
class ControlProvider;
class ElevatorController : public Simulatable
{
private:

	SensorProvider* _sensors = nullptr;
	ControlProvider* _controls = nullptr;
	std::queue<int> _stops;
	std::list<int> _stopsVisited;
	float _timeSpentSecs = 0.0f;

public:

	void Init(SensorProvider* sensors, ControlProvider* controls);
	void Step(float deltaTime) override;
	void AddStops(const std::list<int>& floors);
	bool HasStops() { return _stops.size() > 0; }

	const std::list<int>& GetStopsVisited() { return _stopsVisited; }
	float GetTimeSpent() { return _timeSpentSecs; }
};

