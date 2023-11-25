
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
	std::list<int> floorsToVisit;

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
				floorsToVisit.push_back(std::stoi(currFloorText));
			}
		}
	}

    SimulatedElevator simulationTarget;
	ElevatorController controller;

	simulationTarget.setFloor(startingFloor);
	controller.Init(&simulationTarget, &simulationTarget);
	controller.AddStops(floorsToVisit);

	milliseconds prevTimestamp = duration_cast<milliseconds>( system_clock::now().time_since_epoch());
	float timeBankMS = 0;

	while (controller.HasStops())
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

			system("cls");
			std::cout << simulationTarget.GetStateAsString() << std::endl;
		}
	}

	std::ostringstream oss;
	oss << controller.GetTimeSpent() << " ";

	const std::list<int>& stopsVisited = controller.GetStopsVisited();
	bool shouldAddComma = false;
	for (int currVisited : stopsVisited)
	{
		if (shouldAddComma)
			oss << ",";

		if (!shouldAddComma)
			shouldAddComma = true;

		oss << currVisited;
	}

	std::cout << oss.str() << std::endl;
	system("pause");
}

