
#include <iostream>
#include <chrono>
#include "SimulatedElevator.h"
#include "ElevatorController.h"

constexpr float FixedDeltaTime = 1.0f / 60.0f;
constexpr float MillisInSecond = 1000.0f;
int main()
{
	using namespace std::chrono;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    SimulatedElevator simulationTarget;
	ElevatorController controller;

	milliseconds prevTimestamp = duration_cast<milliseconds>( system_clock::now().time_since_epoch());
	float timeBankMS = 0;
	int updateCounter = 0;

	simulationTarget.SetTargetVelocity(100);

	while (true)
	{
		milliseconds nowMS = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		milliseconds delta = nowMS - prevTimestamp;
		prevTimestamp = nowMS;

		// Simple conversion to floating point seconds. This is done to make 
		// integration easier
		timeBankMS += delta.count() / MillisInSecond;

		while (timeBankMS > FixedDeltaTime)
		{
			updateCounter += 1;
			timeBankMS -= FixedDeltaTime;

			simulationTarget.Step(FixedDeltaTime);

			std::cout << simulationTarget.ReadPositionAsMM() << ", " << simulationTarget.ReadStopAlignmentSensor() << std::endl;
		}
	}

}

