#pragma once
#include "ControlProvider.h"
#include "SensorProvider.h"
#include "Simulatable.h"
#include <string>

class SimulatedElevator: public SensorProvider, public ControlProvider, public Simulatable 
{
private:

	float _positionMM = 0;
	float _velocityMMs = 0;
	float _targetVelocityMMs = 0;

	// Ideally should be configurable with a specified measurement per floor, 
	// since constructon will almost never result in mm-perfect landings. But 
	// the input appears to be arbitrary floor numbers with no bounds, so we 
	// will assume a uniform distance in this simulation.
	const int FloorIntervalMM = 3000;
	const int MaxTripHazardHeightMM = 7; // https://www.osha.com/blog/slips-trips-falls-prevention
	const float MaxAccelerationMMs2 = 1200; // https://modularelevator.net/elevator-speeds/

public:

	SimulatedElevator();
	~SimulatedElevator();

	std::string GetStateAsString();

	// Implementation for Simulatable =========================================

	virtual void Step(float deltaTime) override;

	// Implementation for SensorProvider ======================================

	virtual int ReadPositionAsMM() override;

	virtual int ReadVelocityAsMMs() override;

	virtual bool ReadStopAlignmentSensor() override;
	virtual bool ReadIsDoorClosed() override;
	virtual bool ReadIsDoorOpen() override;

	virtual bool ReadAreBreaksEngaged() override;
	virtual bool ReadIsDoorObstructed() override;
	virtual std::vector<int> ReadFloorButtonsPressed() override;

	virtual int ReadLoadKg() override;
	virtual bool ReadEmergencyButtonActive() override;

	virtual bool ReadEmergencyKeyEngaged() override;
	virtual bool ReadSecurityKeyEngaged() override;
	virtual bool ReadMaintenenceKeyEngaged() override;
	
	// Implementation for ControlProvider =====================================

	virtual void SetTargetVelocity(int MMS) override;

	virtual void OpenDoors() override;
	virtual void CloseDoors() override;

	virtual void EngageBrakes() override;
	virtual void ReleaseBrakes() override;

	virtual void DeactivateButtons(std::vector<int> floors) override;
	virtual void DeactivateEmergencyButtons() override;

	// ========================================================================
};

