#include "ElevatorController.h"
#include "SensorProvider.h"
#include "ControlProvider.h"

void ElevatorController::Init(SensorProvider* sensors, ControlProvider* controls)
{
	_sensors = sensors;
	_controls = controls;
}

void ElevatorController::Step(float deltaTime)
{
	if (_stops.size() <= 0)
	{
		_controls->SetTargetVelocity(0);
		return;
	}

	int currPositionMM = _sensors->ReadPositionAsMM();
	int currTargetPos = _stops.front() * 3000;

	if (abs(currTargetPos - currPositionMM) < 7)
	{
		_stops.pop();

		if(_stops.size() > 0)
			currTargetPos = _stops.front() * 3000;
	}

	if (currTargetPos > currPositionMM)
		_controls->SetTargetVelocity(1200);
	else
		_controls->SetTargetVelocity(-1200);
}

void ElevatorController::addStops(std::queue<int> floors)
{
	while (floors.size() > 0) 
	{
		_stops.push(floors.front());
		floors.pop();
	}	
}
