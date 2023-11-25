#include <vector>

// Interface for issuing commands to hardware devices.
class ControlProvider
{

public:

	// Should tell the lift mechanism what velocity to attempt to achieve. Should 
	// sanity check value before sending in case encoders fail to check due to wear/damage.
	virtual void SetTargetVelocity(int MMS) = 0;
	virtual float GetMaxAccelerationMMs2() = 0;

	virtual void OpenDoors() = 0;
	virtual void CloseDoors() = 0;

	virtual void EngageBrakes() = 0;
	virtual void ReleaseBrakes() = 0;

	virtual void DeactivateButtons(std::vector<int> floors) = 0;
	virtual void DeactivateEmergencyButtons() = 0;

};