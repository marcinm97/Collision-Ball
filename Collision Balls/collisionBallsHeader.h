#pragma once
#ifndef collisionBallsHeader
#define collisionBallsHeader
#include "olcConsoleGameEngine.h"
#include <iostream>
#include <string>
#include <vector>


class CirclePhysics :public olcConsoleGameEngine
{
public:
	CirclePhysics();
	virtual bool OnUserCreate() override;
	virtual bool OnUserUpdate(float fElapsedTime) override;
	

};







#endif // !collisionBallsHeader