
#include <iostream>
#include <chrono>
#include <queue>
#include <string>
#include <sstream>
#include "SimulatedElevator.h"
#include "ElevatorController.h"


constexpr float FixedDeltaTime = 1.0f / 60.0f;
constexpr float MillisInSecond = 1000.0f;
constexpr std::string_view StartArgument = "start=";
constexpr std::string_view FloorsArgument = "floors=";
constexpr char FloorDelimeter = ',';

int main(int argc, char* argv[])
{
	using namespace std::chrono;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int startingFloor = 0;
	std::queue<int> floorsToVisit;

	for (int i = 0; i < argc; ++i)
	{
		std::string currArg(argv[i]);
		
		if (currArg._Starts_with(StartArgument))
		{
			std::string numVal = currArg.substr(StartArgument.size());
			startingFloor = std::stoi(numVal);
		}

		if (currArg._Starts_with(FloorsArgument))
		{
			std::string floorVals = currArg.substr(FloorsArgument.size());
			std::stringstream floorsStream(floorVals);

			std::string currFloorText;
			while (std::getline(floorsStream, currFloorText, FloorDelimeter))
			{
				floorsToVisit.push(std::stoi(currFloorText));
			}
		}
	}
		

    SimulatedElevator simulationTarget;
	ElevatorController controller;

	simulationTarget.setFloor(startingFloor);
	controller.Init(&simulationTarget, &simulationTarget);
	controller.addStops(floorsToVisit);

	milliseconds prevTimestamp = duration_cast<milliseconds>( system_clock::now().time_since_epoch());
	float timeBankMS = 0;

	while (controller.hasStops())
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

	system("pause");
}

