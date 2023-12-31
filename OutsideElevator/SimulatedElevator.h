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
	// since constructon will almost never result in mm-perfect landings. Its 
	// even likely that the distance between landings can shift by MM over 
	// time. But the input appears to be arbitrary floor numbers with no 
	// bounds, so we will assume a uniform distance in this simulation.
	const int FloorIntervalMM = 3000;
	const int MaxTripHazardHeightMM = 7; // https://www.osha.com/blog/slips-trips-falls-prevention
	
	const float MaxAccelerationMMs2 = 1200.0f; // https://modularelevator.net/elevator-speeds/
	
	// This is how we get the 10s per floor travel time. The distannce between 
	// each floor is 3000mm so a vel of 300mm/s gets us close to 10s. Actual 
	// travel time will be a little higher due to acceleration and deceleration 
	// periods. I could derive the values necessary to have a 10s per floor 
	// travel time, but that seems sort of contrived for the scope of this 
	// project.
	const float MaxVelocityMMs = 300.0f;

public:

	SimulatedElevator();
	~SimulatedElevator();

	std::string GetStateAsString();
	void setFloor(int _floor);

	// Implementation for Simulatable =========================================

	virtual void Step(float deltaTime) override;

	// Implementation for SensorProvider ======================================

	int ReadPositionAsMM() override;
	
	int ReadVelocityAsMMs() override;
	
	int ReadStopDisplacementAsMM(int floor) override;
	bool ReadStopAlignmentSensor(int floor) override;
	bool ReadIsDoorClosed() override;
	bool ReadIsDoorOpen() override;
	
	bool ReadAreBreaksEngaged() override;
	bool ReadIsDoorObstructed() override;
	std::vector<int> ReadFloorButtonsPressed() override;
	
	int ReadLoadKg() override;
	bool ReadEmergencyButtonActive() override;
	
	bool ReadEmergencyKeyEngaged() override;
	bool ReadSecurityKeyEngaged() override;
	bool ReadMaintenenceKeyEngaged() override;
	
	// Implementation for ControlProvider =====================================

	void SetTargetVelocity(int MMS) override;
	float GetMaxAccelerationMMs2() override;

	void OpenDoors() override;
	void CloseDoors() override;
	
	void EngageBrakes() override;
	void ReleaseBrakes() override;
	
	void DeactivateButtons(std::vector<int> floors) override;
	void DeactivateEmergencyButtons() override;

	// ========================================================================
};

