#include <iostream>
#include "collisionBallsHeader.h"





int main() {
	CirclePhysics game;
	if (game.ConstructConsole(160, 120, 8, 8))
		game.Start();
	else
		std::cout << L"Could not construct console" << std::endl;

	return 0;
}