
#include <iostream>
#include <chrono>
#include "SimulatedElevator.h"
#include "ElevatorController.h"
#include <queue>

constexpr float FixedDeltaTime = 1.0f / 60.0f;
constexpr float MillisInSecond = 1000.0f;
int main()
{
	using namespace std::chrono;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    SimulatedElevator simulationTarget;
	ElevatorController controller;

	controller.Init(&simulationTarget, &simulationTarget);

	std::queue<int> stops;
	stops.push(3);
	stops.push(-3);
	controller.addStops(stops);

	milliseconds prevTimestamp = duration_cast<milliseconds>( system_clock::now().time_since_epoch());
	float timeBankMS = 0;

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
			timeBankMS -= FixedDeltaTime;
			simulationTarget.Step(FixedDeltaTime);
			controller.Step(FixedDeltaTime);
			std::cout << simulationTarget.GetStateAsString() << std::endl;
		}
	}

}

