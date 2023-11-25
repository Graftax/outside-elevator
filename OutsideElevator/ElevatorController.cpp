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

	int displacementMM = _sensors->ReadStopDisplacementAsMM(_stops.front());
	int velMMs = _sensors->ReadVelocityAsMMs();
	int futureDispMM = displacementMM - velMMs;

	// Using the geometric caluclation for deceleration. Since its linear we 
	// can derive the velocity we want from the area of a right triangle where 
	// one side is our acceleration and the other is our distance.
	int maxVel = sqrt(1200.0f * abs(futureDispMM) * 2);
	_controls->SetTargetVelocity(futureDispMM > 0 ? maxVel : -maxVel);
}

void ElevatorController::addStops(std::queue<int> floors)
{
	while (floors.size() > 0) 
	{
		_stops.push(floors.front());
		floors.pop();
	}
}
