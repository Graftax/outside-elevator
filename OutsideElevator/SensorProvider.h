#pragma once
#include <vector>

// Interface for reading sensors. This is the "breaking point" between 
// simluated data and real-world sensors.
class SensorProvider
{

public:

	// Should read from all encoders and convert ticks to mm. Potentially a 
	// great place to throw an exception of multiple encoders provide values 
	// that are not within the tolerance envelope.
	virtual int ReadPositionAsMM() = 0;

	// Should read from all encoders and convert velocity to mm/s. Should also 
	// include encoder sanity checks.
	virtual int ReadVelocityAsMMs() = 0;

	// Should return true if the floor of the elevator is within 7mm of the 
	// floor of any stop.
	virtual bool ReadStopAlignmentSensor() = 0;

	// The value should be true only if the contact sensor between the doors 
	// is engaged.
	virtual bool ReadIsDoorClosed() = 0;

	// The value should be true only if both recessed door contact sensors report true.
	virtual bool ReadIsDoorOpen() = 0;

	// Should return true if any break is not completly released.
	virtual bool ReadAreBreaksEngaged() = 0;

	// Should return true if any IR door sensor reports a distance smaller 
	// than its configured "clear" value.
	virtual bool ReadIsDoorObstructed() = 0;

	// Should return a list of floor buttons that are currently active.
	virtual std::vector<int> ReadFloorButtonsPressed() = 0;

	// Should read from more than one load sensor, then return the value in KG.
	// Needs to make sure that the values are within the tolerance envelope.
	virtual int ReadLoadKg() = 0;

	virtual bool ReadEmergencyButtonActive() = 0;

	// Should return true if any emergency key is inserted and locked.
	virtual bool ReadEmergencyKeyEngaged() = 0;

	// Should return true if any security key is inserted and locked.
	virtual bool ReadSecurityKeyEngaged() = 0;

	// Should return true if any maintence key is inserted and locked.
	virtual bool ReadMaintenenceKeyEngaged() = 0;
};

