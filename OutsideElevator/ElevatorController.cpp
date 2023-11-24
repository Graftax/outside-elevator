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
	if (_stops.size() > 0 && _sensors->ReadStopAlignmentSensor(_stops.front()))
		_stops.pop();

	if (_stops.size() <= 0)
	{
		_controls->SetTargetVelocity(0);
		return;
	}

	if (_sensors->ReadStopDisplacementAsMM(_stops.front()) > 0)
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
