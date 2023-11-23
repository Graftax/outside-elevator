#include "SimulatedElevator.h"
#include <algorithm>


SimulatedElevator::SimulatedElevator()
{

}

SimulatedElevator::~SimulatedElevator()
{

}

void SimulatedElevator::Step(float deltaTime)
{
    // Some lazy, lossy integration, TODO-NICE: Eliminate lossyness.
    // We are assuming perfect acceleration and ignoring the mass of the elevator.

    float acceleration = _targetVelocityMMs - _velocityMMs;

    // Limit acceleration to a reasonable max.
    float limitedAcceleration = std::clamp(acceleration, -MaxAccelerationMMs2, MaxAccelerationMMs2);

    _velocityMMs += (limitedAcceleration * deltaTime);
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

bool SimulatedElevator::ReadStopAlignmentSensor()
{
    int modulus = (int)_positionMM % FloorIntervalMM;
    return abs(modulus) < MaxTripHazardHeightMM;
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
