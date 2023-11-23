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

}

void ElevatorController::addStops(std::queue<int> floors)
{
	
}
