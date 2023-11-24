#include "SimulatedElevator.h"
#include <algorithm>
#include <sstream>

SimulatedElevator::SimulatedElevator()
{

}

SimulatedElevator::~SimulatedElevator()
{

}

std::string SimulatedElevator::GetStateAsString()
{
    std::ostringstream oss;
    oss << _positionMM << ",\t" << _velocityMMs;
    return oss.str();
}

void SimulatedElevator::Step(float deltaTime)
{
    // Some lazy, lossy integration, TODO-NICE: Eliminate lossyness.
    // We are assuming perfect acceleration and ignoring the mass of the elevator.

    float currVelocityDelta = _targetVelocityMMs - _velocityMMs;
    float dir = currVelocityDelta > 0.0f ? 1.0f : -1.0f;

    float acceleration = dir * std::clamp(MaxAccelerationMMs2, 
        -abs(currVelocityDelta),
        abs(currVelocityDelta));

    _velocityMMs += acceleration * deltaTime;
    _positionMM += (_velocityMMs * deltaTime);
}

int SimulatedElevator::ReadPositionAsMM()
{
    return (int)_positionMM;
}

int SimulatedElevator::ReadVelocityAsMMs()
{
    return (int)_velocityMMs;
}

int SimulatedElevator::ReadStopDisplacementAsMM(int floor)
{
    int testPosMM = floor * FloorIntervalMM;
    return (int)(testPosMM - _positionMM);
}

bool SimulatedElevator::ReadStopAlignmentSensor(int floor)
{
    return abs(ReadStopDisplacementAsMM(floor)) < MaxTripHazardHeightMM;
}

bool SimulatedElevator::ReadIsDoorClosed()
{
    return false;
}

bool SimulatedElevator::ReadIsDoorOpen()
{
    return false;
}

bool SimulatedElevator::ReadAreBreaksEngaged()
{
    return false;
}

bool SimulatedElevator::ReadIsDoorObstructed()
{
    return false;
}

std::vector<int> SimulatedElevator::ReadFloorButtonsPressed()
{
    return std::vector<int>();
}

int SimulatedElevator::ReadLoadKg()
{
    return 0;
}

bool SimulatedElevator::ReadEmergencyButtonActive()
{
    return false;
}

bool SimulatedElevator::ReadEmergencyKeyEngaged()
{
    return false;
}

bool SimulatedElevator::ReadSecurityKeyEngaged()
{
    return false;
}

bool SimulatedElevator::ReadMaintenenceKeyEngaged()
{
    return false;
}

void SimulatedElevator::SetTargetVelocity(int mms)
{
    _targetVelocityMMs = (float)mms;
}

void SimulatedElevator::OpenDoors()
{
}

void SimulatedElevator::CloseDoors()
{
}

void SimulatedElevator::EngageBrakes()
{
}

void SimulatedElevator::ReleaseBrakes()
{
}

void SimulatedElevator::DeactivateButtons(std::vector<int> floors)
{
}

void SimulatedElevator::DeactivateEmergencyButtons()
{
}
