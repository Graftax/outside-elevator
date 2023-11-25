# outside-elevator

Those looking for the executables for this project can find them on the [releases page](https://github.com/Graftax/outside-elevator/releases/tag/MVP). Currently only supports Windows, but only because of a couple system commands.

Currently accepts two command line arguments; `start` and `floors`. `start` (optional, defaults to zero) accepts an integer value and will place the elevator on that floor at the start of the simulation. `floors` is required and accepts a comma-separated list of interger values that will define what floors are visited in what order.

`.\OutsideElevator_x64.exe start=1 floors=2,-2,3`

During execution the console shows the current position and velocity of the elevator. When the elevator has visited all floors specified in `floors` the program will output the total time spent traveling and a comma-separated list of each floor it visited in the order that they were visited.

##Assumptions
1. That retrieving values from the sensors occurs immediatly. If you are providing a sensor interface you must provide a value synchronously.
3. That the encoders on your lift mechanism have an accuracy of at least 1 millimeter. If the encoders you use are less accurate than 3mm it could result in intolerable misalignment.
4. That buttons can only be activated by passengers, there is no mechanism for the controller to cause a button to become activated, or for one to be activated via signals external to the elevator loop.
5. That your floors are all evenly spaced. If you have significant deviations in your travel distances, it is currently not possible to compensate.
6. That your elevator is in the United States. No attempt as been made to comply with safety standards from other regions.
7. That you will be executing this on hardware that is capable of running the program at 60 updates per second. Running it on especially low-power devices could result in latency or overshooting/undershooting floor position targets.
8. That your building is infinitely tall and immune to the heat and pressure of the core of the earth, in addition to the pressure-differential and radiation present outside the atmosphere.
   
##Unimplemented Features
1. Door control. The controller currently will not drive door operation, and the simulation environment does not implemented door movement.
2. Brake control. The controller currently assumes that breaks are off and never engaged. The simulation does not account for brakes.
3. Button state is not implemented in the simulation, and the controller currently does not listen for button states. 
4. Floor selection is currently not implemented. The target floor is injected in to the controller directly instead of being read through the buttons in the sensor interface.
5. Load detection. The weight of the carriage and the weight of the passgers is currently not taken in to account by the simulation or the controller.
6. Emergency overrides are not implemented, if an emergency button is pressed or an emergency key engaged, there will be no change in the behavior of the elevator.
7. Passenger boarding/exiting is not implemented.
8. Security overrides are not implemented.
9. Maintenence mode is not implemented.
